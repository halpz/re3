all: im2d_gl3.inc colourfilterVC_fs_gl3.inc contrast_fs_gl3.inc

im2d_gl3.inc: im2d.vert
	(echo 'const char *im2d_vert_src =';\
	 sed 's/..*/"&\\n"/' im2d.vert;\
	 echo ';') >im2d_gl3.inc

colourfilterVC_fs_gl3.inc: colourfilterVC.frag
	(echo 'const char *colourfilterVC_frag_src =';\
	 sed 's/..*/"&\\n"/' colourfilterVC.frag;\
	 echo ';') >colourfilterVC_fs_gl3.inc

contrast_fs_gl3.inc: contrast.frag
	(echo 'const char *contrast_frag_src =';\
	 sed 's/..*/"&\\n"/' contrast.frag;\
	 echo ';') >contrast_fs_gl3.inc
