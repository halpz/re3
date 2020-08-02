
/* If this file is used outside of the core RW SDK, 
 * the following things need to be defined 
 */
#if (!defined(RWASSERT))
#define RWASSERT(_assertval)   /* No op */
#endif
#if (!defined(RWFUNCTION))
#define RWFUNCTION(_rwfunctionstring) /* No op */
#endif
#if (!defined(RWRETURN))
#define RWRETURN(_rwreturnval) return(_rwreturnval)
#endif
#if (!defined(RWRETURNVOID))
#define RWRETURNVOID() return
#endif

/* These are used by specular lighting, 
 * sorry I have to leave them in here... IDBS
 * I'll make it neater when I have time. 
 */
#if (!defined(FALLOFFAMBIENT))
#define FALLOFFAMBIENT()       /* No op */
#endif
#if (!defined(FALLOFFDIRECTIONAL))
#define FALLOFFDIRECTIONAL()   /* No op */
#endif
#if (!defined(FALLOFFPOINT))
#define FALLOFFPOINT()         /* No op */
#endif
#if (!defined(FALLOFFSPOT))
#define FALLOFFSPOT()          /* No op */
#endif
#if (!defined(FALLOFFSOFTSPOT))
#define FALLOFFSOFTSPOT()      /* No op */
#endif

/***************************************************************************
 _rwApplyAmbientLight

 On entry   : Instanced data
            : Light
            : Optional inverse object matrix 
            : (to transform light to object space)
            : Inverse scale of object
            : Surface properties of the light
 On exit    :
 */

static void
_rwApplyAmbientLight(VERTSARG,
                  const void *voidLight,
                  const RwMatrix * __RWUNUSED__ inverseMat,
                  RwReal __RWUNUSED__ invScale,
                  const RwSurfaceProperties * surfaceProps)
{
    CAMVERTDECL;
    NUMVERTDECL;
    const RpLight      *light = (const RpLight *) voidLight;
    RwReal              scale;
    RwV3d               vertToLight;

    RWFUNCTION(RWSTRING("_rwApplyAmbientLight"));
    RWASSERT(light);
    RWASSERT(surfaceProps);

    CAMVERTINIT();
    NUMVERTINIT();

    /* No directional component: 
     * (this is used in CAMVERTADDRGBA in a specular lighting node) */
    vertToLight.x = 0;
    vertToLight.y = 0;
    vertToLight.z = 0;

    /* rpLIGHTAMBIENT - Constant illumination on all vertices
     */
    if (rwObjectTestPrivateFlags(light, rpLIGHTPRIVATENOCHROMA))
    {
        scale = 255.0f * light->color.red * surfaceProps->ambient;

        /* Ambient light affects all vertices the same */
        while (numVert--)
        {
            RwReal              lum = scale;

#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFAMBIENT
            CAMVERTADDRGBA(1, 1, 1, 0);
            CAMVERTINC();
        }
    }
    else
        /* perform for coloured lights */
    {
        scale = 255.0f * surfaceProps->ambient;

        /* Ambient light affects all vertices the same */
        while (numVert--)
        {
            RwReal              lum = scale;

#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFAMBIENT
            CAMVERTADDRGBA(light->color.red, light->color.green,
                           light->color.blue, 0);
            CAMVERTINC();
        }
    }
    RWRETURNVOID();
}

/***************************************************************************
 _rwApplyDirectionalLight

 On entry   : Instanced data
            : Light
            : Optional inverse object matrix
            : (to transform light to object space)
            : Inverse scale of object
            : Surface properties of the light
 On exit    :
 */

static void
_rwApplyDirectionalLight(VERTSARG,
                      const void *voidLight,
                      const RwMatrix * inverseMat,
                      RwReal __RWUNUSED__ invScale,
                      const RwSurfaceProperties * surfaceProps)
{
    OBJCAMVERTDECL;
    NUMVERTDECL;
    const RpLight      *light = (const RpLight *) voidLight;
    RwV3d               vertToLight;
    RwReal              scale;
    RwReal              dot;
    RwFrame            *lightFrame;

    RWFUNCTION(RWSTRING("_rwApplyDirectionalLight"));
    RWASSERT(light);
    RWASSERT(surfaceProps);

    OBJCAMVERTINIT();
    NUMVERTINIT();

    /* rpLIGHTDIRECTIONAL - Lighting scaled by dot product
     * of vertex normal and light lookAt vector.
     */
    /* This may not have a frame - we need to check */
    lightFrame = RpLightGetFrame(light);
    if (lightFrame)
    {
        vertToLight = RwFrameGetLTM(lightFrame)->at;

        /* Transform the light into object space if necessary */
        if (inverseMat)
        {
            RwV3dTransformVectors(&vertToLight, &vertToLight, 1, inverseMat);
            _rwV3dNormalize(&vertToLight, &vertToLight);
        }

        /* Vert TO light */
        RwV3dScale(&vertToLight, &vertToLight, -1);

        /* Optimise for grey lights? */
        if (rwObjectTestPrivateFlags(light, rpLIGHTPRIVATENOCHROMA))
        {
            /* Use one of the light colour intensities as general intensity */
            /* light vector tests are to be identical to others */
            scale = 255.0f * light->color.red * surfaceProps->diffuse;

            /* Loop through each of the vertices */
            while (numVert--)
            {
                RwV3d               objNormal;

                OBJVERTGETNORMAL(&objNormal);
                /* Calculate angle between vertex normal and light vector */
                dot = RwV3dDotProduct(&vertToLight, &objNormal);

                /* Ensure vector is facing light, 
                 * don't light areas not facing */

                if (dot > 0.0f)
                {
                    RwReal              lum = dot * scale;

#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFDIRECTIONAL
                    CAMVERTADDRGBA(1, 1, 1, 0);
                }

                /* Next vertex */
                OBJCAMVERTINC();
            }
        }
        else
            /* perform for coloured lights */
        {
            scale = 255.0f * surfaceProps->diffuse;

            /* Loop through each of the vertices */
            while (numVert--)
            {
                RwV3d               objNormal;

                OBJVERTGETNORMAL(&objNormal);
                /* Calculate angle between vertex normal and light vector */
                dot = RwV3dDotProduct(&vertToLight, &objNormal);

                /* Ensure vector is facing light, 
                 * don't light areas not facing */

                if (dot > 0.0f)
                {
                    RwReal              lum = dot * scale;

#define FALLOFFCALC FALLOFFDIRECTIONAL
                    CAMVERTADDRGBA(light->color.red, light->color.green,
                                   light->color.blue, 0);
                }

                /* Next vertex */
                OBJCAMVERTINC();
            }
        }
    }

    RWRETURNVOID();
}

/***************************************************************************
 _rwApplyPointLight

 On entry   : Instanced data
            : Light
            : Optional inverse object matrix 
            : (to transform light to object space)
            : Inverse scale of object
            : Surface properties of the light
 On exit    :
 */

static void
_rwApplyPointLight(VERTSARG, const void *voidLight,
                const RwMatrix * inverseMat,
                RwReal invScale, const RwSurfaceProperties * surfaceProps)
{
    OBJCAMVERTDECL;
    NUMVERTDECL;
    const RpLight      *light = (const RpLight *) voidLight;
    RwReal              scale, recipRad;
    RwV3d               lightPos, vertToLight;
    RwReal              radSquared;

    RWFUNCTION(RWSTRING("_rwApplyPointLight"));
    RWASSERT(light);
    RWASSERT(surfaceProps);

    OBJCAMVERTINIT();
    NUMVERTINIT();

    /* rpLIGHTPOINT - Linear falloff with distance, scaled by
     * dot product of vertex normal and light to vertex vector.
     */
    lightPos = RwFrameGetLTM(RpLightGetFrame(light))->pos;

    if (inverseMat)
    {
        RwReal              scaledRad;

        scaledRad = ((light->radius) * (invScale));
        radSquared = ((scaledRad) * (scaledRad));
        recipRad = (((RwReal) (1)) / (scaledRad));

        /* Transform light into object space */
        RwV3dTransformPoints(&lightPos, &lightPos, 1, inverseMat);
    }
    else
    {
        radSquared = ((light->radius) * (light->radius));
        recipRad = (((RwReal) (1)) / (light->radius));
    }

    if (rwObjectTestPrivateFlags(light, rpLIGHTPRIVATENOCHROMA))
    {
        /* The scale encapsulates the common elements to do
         * with light intensity and surface lighting properties
         */
        scale =
            ((((RwReal) (255)) * (light->color.red))) *
            (surfaceProps->diffuse);

        while (numVert--)
        {
            RwV3d               objVertex, objNormal;
            RwReal              dot, dist2;

            OBJVERTGETPOS(&objVertex);
            OBJVERTGETNORMAL(&objNormal);

            /* Discover the vector between vertex and light and it's length */
            RwV3dSub(&vertToLight, &lightPos, &objVertex);

            /* Ensure that this vertex is facing the light source */
            dot = RwV3dDotProduct(&vertToLight, &objNormal);
            if (dot > 0.0f)
            {
                /* Ensure vertex lies within the light's radius */
                dist2 = RwV3dDotProduct(&vertToLight, &vertToLight);
                if (dist2 < radSquared)
                {
                    RwReal              lum;
                    RwReal              recipDist;
                    RwReal              dist;

                    rwSqrt(&dist, dist2);
                    recipDist =
                        (dist > 0.0f) ? (((RwReal) 1) / dist) : 0.0f;

                    /*
                     * The following simplifies down to:
                     * 
                     *  -scale * 
                     *  (dot/dist) * 
                     *  (1 - dist/lightRadius)
                     * 
                     * Where
                     *   scale
                     *      takes care of the light intensity and 
                     *      diffuse lighting coefficient 
                     *   (dot/dist) 
                     *     is a normalised dot product of 
                     *     light->vertex vector and vertex normal
                     *   (1 - dist/lightRadius) 
                     *      is a linear falloff factor
                     */
                    lum = scale * dot * (recipDist - recipRad);

                    /* Calculate the luminance at vertex */
#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFPOINT
                    CAMVERTADDRGBA(1, 1, 1, 0);
                }
            }

            OBJCAMVERTINC();
        }
    }
    else
    {
        scale = (((RwReal) (255)) * (surfaceProps->diffuse));

        while (numVert--)
        {
            RwV3d               objVertex, objNormal;
            RwReal              dot, dist2;

            OBJVERTGETPOS(&objVertex);
            OBJVERTGETNORMAL(&objNormal);

            /* Discover the vector between vertex and light and it's length */
            RwV3dSub(&vertToLight, &lightPos, &objVertex);

            /* Ensure that this vertex is facing the light source */
            dot = RwV3dDotProduct(&vertToLight, &objNormal);
            if (dot > 0.0f)
            {
                dist2 = RwV3dDotProduct(&vertToLight, &vertToLight);

                /* Ensure vertex lies within the light's radius */
                if (dist2 < radSquared)
                {
                    RwReal              lum;
                    RwReal              recipDist;
                    RwReal              dist;

                    /* Only now calculate the actual length of vector */
                    rwSqrt(&dist, dist2);
                    recipDist =
                        (dist > 0.0f) ? (((RwReal) 1) / dist) : 0.0f;

                    lum = scale * dot * (recipDist - recipRad);
                    /* Alter the luminance according to light colour */
#define FALLOFFCALC FALLOFFPOINT
                    CAMVERTADDRGBA(light->color.red, light->color.green,
                                   light->color.blue, 0);
                }
            }

            /* Next point */
            OBJCAMVERTINC();
        }
    }
    RWRETURNVOID();
}

/***************************************************************************
 _rwApplySpotLight

 On entry   : Instanced data
            : Light
            : Optional inverse object matrix 
            : (to transform light to object space)
            : Inverse scale of object
            : Surface properties of the light
 On exit    :
 */

static void
_rwApplySpotLight(VERTSARG,
               const void *voidLight,
               const RwMatrix * inverseMat,
               RwReal invScale, const RwSurfaceProperties * surfaceProps)
{
    OBJCAMVERTDECL;
    NUMVERTDECL;
    const RpLight      *light = (const RpLight *) voidLight;
    RwReal              recipRad;
    RwReal              radSquared;
    RwV3d               lightPos, at;

    RWFUNCTION(RWSTRING("_rwApplySpotLight"));
    RWASSERT(light);
    RWASSERT(surfaceProps);

    OBJCAMVERTINIT();
    NUMVERTINIT();

    /* rpLIGHTSPOT - Linear falloff with distance, cone to restrict
     * angle that light has effect, constant intensity across cone,
     * scaled by dot product of vertex normal and light to vertex vector.
     */

    lightPos = RwFrameGetLTM(RpLightGetFrame(light))->pos;
    at = RwFrameGetLTM(RpLightGetFrame(light))->at;

    if (inverseMat)
    {
        RwReal              scaledRad;

        scaledRad = ((light->radius) * (invScale));
        recipRad = (((RwReal) (1)) / (scaledRad));
        radSquared = ((scaledRad) * (scaledRad));

        /* Transform light into object space */
        /* The at is required to ensure within cone */
        RwV3dTransformPoints(&lightPos, &lightPos, 1, inverseMat);
        RwV3dTransformVectors(&at, &at, 1, inverseMat);
        _rwV3dNormalize(&at, &at);
    }
    else
    {
        recipRad = (((RwReal) (1)) / (light->radius));
        radSquared = ((light->radius) * (light->radius));
    }

    if (rwObjectTestPrivateFlags(light, rpLIGHTPRIVATENOCHROMA))
    {
        RwReal              scale =

            ((RwReal) 255) * (light->color.red) * (surfaceProps->diffuse);

        while (numVert--)
        {
            RwV3d               vertToLight, objVertex, objNormal;
            RwReal              dot;

            OBJVERTGETPOS(&objVertex);
            OBJVERTGETNORMAL(&objNormal);

            /* Find the squared distance from light point to vertex */
            RwV3dSub(&vertToLight, &lightPos, &objVertex);

            /* Ensure that this vertex is facing the light source */
            dot = RwV3dDotProduct(&vertToLight, &objNormal);
            if (dot > 0.0f)
            {
                RwReal              dist2;

                /* Ensure vertex lies within the light's radius */
                dist2 = RwV3dDotProduct(&vertToLight, &vertToLight);
                if (dist2 < radSquared)
                {
                    RwReal              dist;
                    RwReal              compare;
                    RwReal              proj;

                    rwSqrt(&dist, dist2);
                    compare = dist * light->minusCosAngle;
                    proj = RwV3dDotProduct(&vertToLight, &at);

                    if (proj < compare)
                    {
                        RwReal              lum;
                        RwReal              recipDist;

                        /* Get the real distance from the light 
                         * to the vertex (not squared) */
                        recipDist =
                            (dist > 0.0f) ? (((RwReal) 1) / dist) : 0.0f;

                        /* This model is the same as the point source 
                         * inside the cone, zero outside the cone */
                        lum = scale * dot * (recipDist - recipRad);
#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFSPOT
                        CAMVERTADDRGBA(1, 1, 1, 0);
                    }
                }
                /* Next vertex */
                OBJCAMVERTINC();
            }
        }
    }
    else
    {
        RwReal              scale =

            (((RwReal) (255)) * (surfaceProps->diffuse));

        while (numVert--)
        {
            RwV3d               vertToLight, objVertex, objNormal;
            RwReal              dot;

            OBJVERTGETPOS(&objVertex);
            OBJVERTGETNORMAL(&objNormal);

            /* Find the squared distance from light point to vertex */
            RwV3dSub(&vertToLight, &lightPos, &objVertex);

            /* Ensure that this vertex is facing the light source */
            dot = RwV3dDotProduct(&vertToLight, &objNormal);
            if (dot > 0.0f)
            {
                RwReal              dist2;

                /* Ensure vertex lies within the light's radius */
                dist2 = RwV3dDotProduct(&vertToLight, &vertToLight);
                if (dist2 < radSquared)
                {
                    RwReal              dist;
                    RwReal              compare;
                    RwReal              proj;

                    rwSqrt(&dist, dist2);
                    compare = dist * light->minusCosAngle;
                    proj = RwV3dDotProduct(&vertToLight, &at);

                    if (proj < compare)
                    {
                        RwReal              lum;
                        RwReal              recipDist;

                        recipDist =
                            (dist > 0.0f) ? (((RwReal) 1) / dist) : 0.0f;

                        /* This model is the same as the point source 
                         * inside the cone, zero outside the cone */
                        lum = scale * dot * (recipDist - recipRad);

                        /* Introduce the light colours as a 
                         * scaling factor for luminance */
#define FALLOFFCALC FALLOFFSPOT
                        CAMVERTADDRGBA(light->color.red,
                                       light->color.green, light->color.blue,
                                       0);
                    }
                }
            }

            /* Next */
            OBJCAMVERTINC();
        }
    }

    RWRETURNVOID();
}

/***************************************************************************
 _rwApplySpotSoftLight

 On entry   : Instanced data
            : Light
            : Optional inverse object matrix
            : (to transform light to object space)
            : Inverse scale of object
            : Surface properties of the light
 On exit    :
 */

static void
_rwApplySpotSoftLight(VERTSARG, const void *voidLight,
                   const RwMatrix * inverseMat, RwReal invScale,
                   const RwSurfaceProperties * surfaceProps)
{
    OBJCAMVERTDECL;
    NUMVERTDECL;
    const RpLight      *light = (const RpLight *) voidLight;
    RwReal              recipRad;
    RwReal              radSquared;
    RwV3d               lightPos, at;

    RWFUNCTION(RWSTRING("_rwApplySpotSoftLight"));
    RWASSERT(light);
    RWASSERT(surfaceProps);

    OBJCAMVERTINIT();
    NUMVERTINIT();

    /* rpLIGHTSPOTSOFT - Linear falloff with distance, cone to restrict
     * angle that light has effect, falloff to edge of cone, scaled by
     * dot product of vertex normal and light to vertex vector.
     */

    lightPos = RwFrameGetLTM(RpLightGetFrame(light))->pos;
    at = RwFrameGetLTM(RpLightGetFrame(light))->at;

    if (inverseMat)
    {
        RwReal              scaledRad;

        scaledRad = ((light->radius) * (invScale));
        recipRad = (((RwReal) (1)) / (scaledRad));
        radSquared = ((scaledRad) * (scaledRad));

        /* Transform light into object space */
        /* The at is required to ensure within cone */
        RwV3dTransformPoints(&lightPos, &lightPos, 1, inverseMat);
        RwV3dTransformVectors(&at, &at, 1, inverseMat);
        _rwV3dNormalize(&at, &at);
    }
    else
    {
        recipRad = 1.0f / light->radius;
        radSquared = light->radius * light->radius;
    }

    if (rwObjectTestPrivateFlags(light, rpLIGHTPRIVATENOCHROMA))
    {
        RwReal              scale =

            ((RwReal) 255) * (light->color.red) * (surfaceProps->diffuse);

        while (numVert--)
        {
            RwV3d               vertToLight, objVertex, objNormal;
            RwReal              dot;

            OBJVERTGETPOS(&objVertex);
            OBJVERTGETNORMAL(&objNormal);

            /* Find the squared distance from light point to vertex */
            RwV3dSub(&vertToLight, &lightPos, &objVertex);

            /* Ensure that this vertex is facing the light source */
            dot = RwV3dDotProduct(&vertToLight, &objNormal);
            if (dot > 0.0f)
            {
                RwReal              dist2;

                /* Ensure vertex lies within the light's radius */
                dist2 = RwV3dDotProduct(&vertToLight, &vertToLight);
                if (dist2 < radSquared)
                {
                    RwReal              dist;
                    RwReal              compare;
                    RwReal              proj;

                    rwSqrt(&dist, dist2);
                    compare = dist * light->minusCosAngle;
                    proj = RwV3dDotProduct(&vertToLight, &at);

                    if (proj < compare)
                    {
                        RwReal              lum;
                        RwReal              recipDist;
                        RwReal              normalise;

                        recipDist =
                            (dist > 0.0f) ? (((RwReal) 1) / dist) : 0.0f;

                        /* This model is the same as the point source 
                         * inside the cone, zero outside the cone */
                        lum = scale * dot * (recipDist - recipRad);

                        /* It has an extra term for quadratic falloff 
                         * across the cone though */
                        normalise = (dist + compare);
                        RWASSERT(normalise >= 0.0f);
                        if (normalise > 0.0f)
                        {
                            normalise = (dist + proj) / normalise;

                            normalise *= normalise;
                            lum *= (((RwReal) 1) - normalise);
                        }

#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFSOFTSPOT
                        CAMVERTADDRGBA(1, 1, 1, 0);
                    }
                }
            }

            /* Next */
            OBJCAMVERTINC();
        }
    }

    else
    {
        RwReal              scale = 255.0f * surfaceProps->diffuse;

        while (numVert--)
        {
            RwV3d               vertToLight, objVertex, objNormal;
            RwReal              dot;

            OBJVERTGETPOS(&objVertex);
            OBJVERTGETNORMAL(&objNormal);

            /* Find the squared distance from light point to vertex */
            RwV3dSub(&vertToLight, &lightPos, &objVertex);

            /* Ensure that this vertex is facing the light source */
            dot = RwV3dDotProduct(&vertToLight, &objNormal);
            if (dot > 0.0f)
            {
                RwReal              dist2;

                /* Ensure vertex lies within the light's radius */
                dist2 = RwV3dDotProduct(&vertToLight, &vertToLight);
                if (dist2 < radSquared)
                {
                    RwReal              dist;
                    RwReal              compare;
                    RwReal              proj;

                    rwSqrt(&dist, dist2);
                    compare = dist * light->minusCosAngle;
                    proj = RwV3dDotProduct(&vertToLight, &at);

                    if (proj < compare)
                    {

                        RwReal              lum;
                        RwReal              normalise;
                        RwReal              recipDist;

                        /* Get the real distance from the light 
                         * to the vertex (not squared) */
                        recipDist =
                            (dist > 0.0f) ? (((RwReal) 1) / dist) : 0.0f;

                        /* This model is the same as the point source
                         * inside the cone, zero outside the cone */
                        lum = scale * dot * (recipDist - recipRad);

                        /* It has an extra term for quadratic falloff 
                         * across the cone though */
                        /* It has an extra term for quadratic falloff 
                         * across the cone though */
                        normalise = (dist + compare);
                        RWASSERT(normalise >= 0.0f);
                        if (normalise > 0.0f)
                        {
                            normalise = (dist + proj) / normalise;

                            normalise *= normalise;
                            lum *= (((RwReal) 1) - normalise);

                        }
                        /* Introduce the light colours as a 
                         * scaling factor for luminance */
#undef  FALLOFFCALC
#define FALLOFFCALC FALLOFFSOFTSPOT
                        CAMVERTADDRGBA(light->color.red,
                                       light->color.green,
                                       light->color.blue, 0);
                    }
                }
            }

            /* Next */
            OBJCAMVERTINC();
        }
    }

    RWRETURNVOID();
}
