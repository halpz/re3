# Intro

The aim of this project is to reverse GTA III for PC by replacing
parts of the game [one by one](https://en.wikipedia.org/wiki/Ship_of_Theseus)
such that we have a working game at all times.

Apparently you can download a binary of the latest version
[here](https://ci.appveyor.com/api/projects/aap/re3/artifacts/bin%2FReleaseCI%2Fre3.dll?branch=master).

Re3 starts the script main_freeroam.scm by default. Make sure you copy it to your data directory.

# Strategy

A good approach is to start at the fringes of the code base,
i.e. classes that don't depend on code that we don't have reversed yet.
If a function uses only few unreversed functions that would be inconvenient
to reverse at the time, calling the original functions is acceptable.

# Progress

This is a list of some things that have been reversed to some non-trivial extent.
Not everything is listed, check the code.

```
CPool
CTxdStore
CVector
CVector2D
CMatrix
CModelInfo
CBaseModelInfo
CSimpleModelInfo
CTimeModelInfo
CClumpModelInfo
CPedModelInfo
CVehicleModelInfo
CVisibilityPlugins
CRenderer
CSprite
CSprite2d
CFont
CEntity
CPhysical
CCollision
CCullZones
CTheZones
CPathFind
CCam
CParticle
CParticleMgr
```

# Low hanging fruit

There are a couple of things that have been reversed for other projects
already that could probably be put into this project without too much effort.
Again, the list is not complete:

* ~~Animation (https://github.com/aap/iii_anim)~~
* File Loader (https://github.com/aap/librwgta/tree/master/tools/IIItest)
* ...

# Coding style

I started writing in [Plan 9 style](http://man.cat-v.org/plan_9/6/style),
but realize that this is not the most popular style, so I'm willing to compromise.
Try not to deviate too much so the code will look similar across the whole project.

To give examples, these two styles (or anything in between) are fine:

```
type
functionname(args)
{
	if(a == b){
		s1;
		s2;
	}
	if(x != y)
		s3;
}

type functionname(args)
{
	if (a == b) {
		s1;
		s2;
	}
	if (x != y)
		s3;
}
```

This one (or anything more extreme) is heavily discouraged:

```
type functionname ( args )
{
  if ( a == b )
  {
    s1;
    s2;
  }
  if ( x != y )
  {
    s3;
  }
}
```

Indentation is done with TABS.

