$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) ALIGNED_MALLOC.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) ALPHA.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) COLORBARS.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) COLORS.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) ERASE.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) FADE.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) GRABCLIENT.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) GRABSCREEN.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) HSV.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) LOGO.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) MINIXPM.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) OVERLAY.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) RESOURCES.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) SPLINE.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) TEXTCLIENT.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) THREAD_UTIL.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) USLEEP.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) VISUAL.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) VISUAL-GL.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) VMS-GTOD.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) VMS-STRDUP.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) XDBE.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) XMU.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) XSHM.C
$ CC/DECC/PREFIX=ALL/DEFINE=(VMS,HAVE_CONFIG_H)/INCL=([],[-]) YARANDOM.C
$ lib/cre utils.olb_decc
$ lib utils.olb_decc *.obj
$! delete/noconf *.obj;
