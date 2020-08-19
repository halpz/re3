all: im2d_gl3.inc simple_fs_gl3.inc default_UV2_gl3.inc \
	colourfilterIII_fs_gl3.inc contrast_fs_gl3.inc \
	neoRim_gl3.inc neoRimSkin_gl3.inc \
	neoWorldIII_fs_gl3.inc neoGloss_vs_gl3.inc neoGloss_fs_gl3.inc \
	neoVehicle_vs_gl3.inc neoVehicle_fs_gl3.inc

im2d_gl3.inc: im2d.vert
	(echo 'const char *im2d_vert_src =';\
	 sed 's/..*/"&\\n"/' im2d.vert;\
	 echo ';') >im2d_gl3.inc

simple_fs_gl3.inc: simple.frag
	(echo 'const char *simple_frag_src =';\
	 sed 's/..*/"&\\n"/' simple.frag;\
	 echo ';') >simple_fs_gl3.inc

default_UV2_gl3.inc: default_UV2.vert
	(echo 'const char *default_UV2_vert_src =';\
	 sed 's/..*/"&\\n"/' default_UV2.vert;\
	 echo ';') >default_UV2_gl3.inc



colourfilterIII_fs_gl3.inc: colourfilterIII.frag
	(echo 'const char *colourfilterIII_frag_src =';\
	 sed 's/..*/"&\\n"/' colourfilterIII.frag;\
	 echo ';') >colourfilterIII_fs_gl3.inc

contrast_fs_gl3.inc: contrast.frag
	(echo 'const char *contrast_frag_src =';\
	 sed 's/..*/"&\\n"/' contrast.frag;\
	 echo ';') >contrast_fs_gl3.inc


neoRim_gl3.inc: neoRim.vert
	(echo 'const char *neoRim_vert_src =';\
	 sed 's/..*/"&\\n"/' neoRim.vert;\
	 echo ';') >neoRim_gl3.inc

neoRimSkin_gl3.inc: neoRimSkin.vert
	(echo 'const char *neoRimSkin_vert_src =';\
	 sed 's/..*/"&\\n"/' neoRimSkin.vert;\
	 echo ';') >neoRimSkin_gl3.inc

neoWorldIII_fs_gl3.inc: neoWorldIII.frag
	(echo 'const char *neoWorldIII_frag_src =';\
	 sed 's/..*/"&\\n"/' neoWorldIII.frag;\
	 echo ';') >neoWorldIII_fs_gl3.inc

neoGloss_fs_gl3.inc: neoGloss.frag
	(echo 'const char *neoGloss_frag_src =';\
	 sed 's/..*/"&\\n"/' neoGloss.frag;\
	 echo ';') >neoGloss_fs_gl3.inc

neoGloss_vs_gl3.inc: neoGloss.vert
	(echo 'const char *neoGloss_vert_src =';\
	 sed 's/..*/"&\\n"/' neoGloss.vert;\
	 echo ';') >neoGloss_vs_gl3.inc

neoVehicle_vs_gl3.inc: neoVehicle.vert
	(echo 'const char *neoVehicle_vert_src =';\
	 sed 's/..*/"&\\n"/' neoVehicle.vert;\
	 echo ';') >neoVehicle_vs_gl3.inc

neoVehicle_fs_gl3.inc: neoVehicle.frag
	(echo 'const char *neoVehicle_frag_src =';\
	 sed 's/..*/"&\\n"/' neoVehicle.frag;\
	 echo ';') >neoVehicle_fs_gl3.inc
