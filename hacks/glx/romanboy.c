/* romanboy --- Shows a 3d immersion of the real projective plane
   that rotates in 3d or on which you can walk and that can deform
   smoothly between the Roman surface and the Boy surface. */

#if 0
static const char sccsid[] = "@(#)romanboy.c  1.1 14/10/03 xlockmore";
#endif

/* Copyright (c) 2013-2014 Carsten Steger <carsten@mirsanmir.org>. */

/*
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation.
 *
 * This file is provided AS IS with no warranties of any kind.  The author
 * shall have no liability with respect to the infringement of copyrights,
 * trade secrets or any patents by this file or any part thereof.  In no
 * event will the author be liable for any lost revenue or profits or
 * other special, indirect and consequential damages.
 *
 * REVISION HISTORY:
 * C. Steger - 14/10/03: Initial version
 */

/*
 * This program shows a 3d immersion of the real projective plane
 * that smoothly deforms between the Roman surface and the Boy
 * surface.  You can walk on the projective plane or turn in 3d.  The
 * smooth deformation (homotopy) between these two famous immersions
 * of the real projective plane was constructed by Fran�ois Ap�ry.
 *
 * The real projective plane is a non-orientable surface.  To make
 * this apparent, the two-sided color mode can be used.
 * Alternatively, orientation markers (curling arrows) can be drawn as
 * a texture map on the surface of the projective plane.  While
 * walking on the projective plane, you will notice that the
 * orientation of the curling arrows changes (which it must because
 * the projective plane is non-orientable).
 *
 * The real projective plane is a model for the projective geometry in
 * 2d space.  One point can be singled out as the origin.  A line can
 * be singled out as the line at infinity, i.e., a line that lies at
 * an infinite distance to the origin.  The line at infinity is
 * topologically a circle.  Points on the line at infinity are also
 * used to model directions in projective geometry.  The origin can be
 * visualized in different manners.  When using distance colors, the
 * origin is the point that is displayed as fully saturated red, which
 * is easier to see as the center of the reddish area on the
 * projective plane.  Alternatively, when using distance bands, the
 * origin is the center of the only band that projects to a disk.
 * When using direction bands, the origin is the point where all
 * direction bands collapse to a point.  Finally, when orientation
 * markers are being displayed, the origin the the point where all
 * orientation markers are compressed to a point.  The line at
 * infinity can also be visualized in different ways.  When using
 * distance colors, the line at infinity is the line that is displayed
 * as fully saturated magenta.  When two-sided colors are used, the
 * line at infinity lies at the points where the red and green "sides"
 * of the projective plane meet (of course, the real projective plane
 * only has one side, so this is a design choice of the
 * visualization).  Alternatively, when orientation markers are being
 * displayed, the line at infinity is the place where the orientation
 * markers change their orientation.
 *
 * Note that when the projective plane is displayed with bands, the
 * orientation markers are placed in the middle of the bands.  For
 * distance bands, the bands are chosen in such a way that the band at
 * the origin is only half as wide as the remaining bands, which
 * results in a disk being displayed at the origin that has the same
 * diameter as the remaining bands.  This choice, however, also
 * implies that the band at infinity is half as wide as the other
 * bands.  Since the projective plane is attached to itself (in a
 * complicated fashion) at the line at infinity, effectively the band
 * at infinity is again as wide as the remaining bands.  However,
 * since the orientation markers are displayed in the middle of the
 * bands, this means that only one half of the orientation markers
 * will be displayed twice at the line at infinity if distance bands
 * are used.  If direction bands are used or if the projective plane
 * is displayed as a solid surface, the orientation markers are
 * displayed fully at the respective sides of the line at infinity.
 *
 * The immersed projective plane can be projected to the screen either
 * perspectively or orthographically.  When using the walking modes,
 * perspective projection to the screen will be used.
 *
 * There are three display modes for the projective plane: mesh
 * (wireframe), solid, or transparent.  Furthermore, the appearance of
 * the projective plane can be as a solid object or as a set of
 * see-through bands.  The bands can be distance bands, i.e., bands
 * that lie at increasing distances from the origin, or direction
 * bands, i.e., bands that lie at increasing angles with respect to
 * the origin.
 *
 * When the projective plane is displayed with direction bands, you
 * will be able to see that each direction band (modulo the "pinching"
 * at the origin) is a Moebius strip, which also shows that the
 * projective plane is non-orientable.
 *
 * Finally, the colors with with the projective plane is drawn can be
 * set to two-sided, distance, or direction.  In two-sided mode, the
 * projective plane is drawn with red on one "side" and green on the
 * "other side".  As described above, the projective plane only has
 * one side, so the color jumps from red to green along the line at
 * infinity.  This mode enables you to see that the projective plane
 * is non-orientable.  In distance mode, the projective plane is
 * displayed with fully saturated colors that depend on the distance
 * of the points on the projective plane to the origin.  The origin is
 * displayed in red, the line at infinity is displayed in magenta.  If
 * the projective plane is displayed as distance bands, each band will
 * be displayed with a different color.  In direction mode, the
 * projective plane is displayed with fully saturated colors that
 * depend on the angle of the points on the projective plane with
 * respect to the origin.  Angles in opposite directions to the origin
 * (e.g., 15 and 205 degrees) are displayed in the same color since
 * they are projectively equivalent.  If the projective plane is
 * displayed as direction bands, each band will be displayed with a
 * different color.
 *
 * The rotation speed for each of the three coordinate axes around
 * which the projective plane rotates can be chosen.
 *
 * Furthermore, in the walking mode the walking direction in the 2d
 * base square of the projective plane and the walking speed can be
 * chosen.  The walking direction is measured as an angle in degrees
 * in the 2d square that forms the coordinate system of the surface of
 * the projective plane.  A value of 0 or 180 means that the walk is
 * along a circle at a randomly chosen distance from the origin
 * (parallel to a distance band).  A value of 90 or 270 means that the
 * walk is directly from the origin to the line at infinity and back
 * (analogous to a direction band).  Any other value results in a
 * curved path from the origin to the line at infinity and back.
 *
 * By default, the immersion of the real projective plane smoothly
 * deforms between the Roman and Boy surfaces.  It is possible to
 * choose the speed of the deformation.  Furthermore, it is possible
 * to switch the deformation off.  It is also possible to determine
 * the initial deformation of the immersion.  This is mostly useful if
 * the deformation is switched off, in which case it will determine
 * the appearance of the surface.
 *
 * As a final option, it is possible to display generalized versions
 * of the immersion discussed above by specifying the order of the
 * surface.  The default surface order of 3 results in the immersion
 * of the real projective described above.  The surface order can be
 * chosen between 2 and 9.  Odd surface orders result in generalized
 * immersions of the real projective plane, while even numbers result
 * in a immersion of a topological sphere (which is orientable).  The
 * most interesting even case is a surface order of 2, which results
 * in an immersion of the halfway model of Morin's sphere eversion (if
 * the deformation is switched off).
 *
 * This program is inspired by Fran�ois Ap�ry's book "Models of the
 * Real Projective Plane", Vieweg, 1987.
 */

#include "curlicue.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DISP_WIREFRAME             0
#define DISP_SURFACE               1
#define DISP_TRANSPARENT           2
#define NUM_DISPLAY_MODES          3

#define APPEARANCE_SOLID           0
#define APPEARANCE_DISTANCE_BANDS  1
#define APPEARANCE_DIRECTION_BANDS 2
#define NUM_APPEARANCES            3

#define COLORS_TWOSIDED            0
#define COLORS_DISTANCE            1
#define COLORS_DIRECTION           2
#define NUM_COLORS                 3

#define VIEW_WALK                  0
#define VIEW_TURN                  1
#define NUM_VIEW_MODES             2

#define DISP_PERSPECTIVE           0
#define DISP_ORTHOGRAPHIC          1
#define NUM_DISP_MODES             2

#define DEF_DISPLAY_MODE           "random"
#define DEF_APPEARANCE             "random"
#define DEF_COLORS                 "random"
#define DEF_VIEW_MODE              "random"
#define DEF_MARKS                  "False"
#define DEF_DEFORM                 "True"
#define DEF_PROJECTION             "random"
#define DEF_SPEEDX                 "1.1"
#define DEF_SPEEDY                 "1.3"
#define DEF_SPEEDZ                 "1.5"
#define DEF_WALK_DIRECTION         "83.0"
#define DEF_WALK_SPEED             "20.0"
#define DEF_DEFORM_SPEED           "10.0"
#define DEF_INIT_DEFORM            "1000.0"
#define DEF_SURFACE_ORDER          "3"

#ifdef STANDALONE
# define DEFAULTS           "*delay:      10000 \n" \
                            "*showFPS:    False \n" \

# define refresh_romanboy 0
# include "xlockmore.h"         /* from the xscreensaver distribution */
#else  /* !STANDALONE */
# include "xlock.h"             /* from the xlockmore distribution */
#endif /* !STANDALONE */

#ifdef USE_GL

#ifndef HAVE_JWXYZ
# include <X11/keysym.h>
#endif

#include "gltrackball.h"

#include <float.h>


#ifdef USE_MODULES
ModStruct romanboy_description =
{"romanboy", "init_romanboy", "draw_romanboy",
 "release_romanboy", "draw_romanboy", "change_romanboy",
 NULL, &romanboy_opts, 25000, 1, 1, 1, 1.0, 4, "",
 "Rotate a 3d immersion of the real projective plane in 3d or walk on it",
 0, NULL};

#endif


static char *mode;
static int display_mode;
static char *appear;
static int appearance;
static char *color_mode;
static int colors;
static char *view_mode;
static int view;
static Bool marks;
static Bool deform;
static char *proj;
static int projection;
static float speed_x;
static float speed_y;
static float speed_z;
static float walk_direction;
static float walk_speed;
static float deform_speed;
static float init_deform;
static int surface_order;


static XrmOptionDescRec opts[] =
{
  {"-mode",                ".displayMode",   XrmoptionSepArg, 0 },
  {"-wireframe",           ".displayMode",   XrmoptionNoArg,  "wireframe" },
  {"-surface",             ".displayMode",   XrmoptionNoArg,  "surface" },
  {"-transparent",         ".displayMode",   XrmoptionNoArg,  "transparent" },
  {"-appearance",          ".appearance",    XrmoptionSepArg, 0 },
  {"-solid",               ".appearance",    XrmoptionNoArg,  "solid" },
  {"-distance-bands",      ".appearance",    XrmoptionNoArg,  "distance-bands" },
  {"-direction-bands",     ".appearance",    XrmoptionNoArg,  "direction-bands" },
  {"-colors",              ".colors",        XrmoptionSepArg, 0 },
  {"-twosided-colors",     ".colors",        XrmoptionNoArg,  "two-sided" },
  {"-distance-colors",     ".colors",        XrmoptionNoArg,  "distance" },
  {"-direction-colors",    ".colors",        XrmoptionNoArg,  "direction" },
  {"-view-mode",           ".viewMode",      XrmoptionSepArg, 0 },
  {"-walk",                ".viewMode",      XrmoptionNoArg,  "walk" },
  {"-turn",                ".viewMode",      XrmoptionNoArg,  "turn" },
  {"-deform",              ".deform",        XrmoptionNoArg, "on"},
  {"+deform",              ".deform",        XrmoptionNoArg, "off"},
  {"-orientation-marks",   ".marks",         XrmoptionNoArg, "on"},
  {"+orientation-marks",   ".marks",         XrmoptionNoArg, "off"},
  {"-projection",          ".projection",    XrmoptionSepArg, 0 },
  {"-perspective",         ".projection",    XrmoptionNoArg,  "perspective" },
  {"-orthographic",        ".projection",    XrmoptionNoArg,  "orthographic" },
  {"-speed-x",             ".speedx",        XrmoptionSepArg, 0 },
  {"-speed-y",             ".speedy",        XrmoptionSepArg, 0 },
  {"-speed-z",             ".speedz",        XrmoptionSepArg, 0 },
  {"-walk-direction",      ".walkDirection", XrmoptionSepArg, 0 },
  {"-walk-speed",          ".walkSpeed",     XrmoptionSepArg, 0 },
  {"-deformation-speed",   ".deformSpeed",   XrmoptionSepArg, 0 },
  {"-initial-deformation", ".initDeform",    XrmoptionSepArg, 0 },
  {"-roman",               ".initDeform",    XrmoptionNoArg,  "0.0" },
  {"-boy",                 ".initDeform",    XrmoptionNoArg,  "1000.0" },
  {"-surface-order",       ".surfaceOrder",  XrmoptionSepArg, 0 },
};

static argtype vars[] =
{
  { &mode,           "displayMode",   "DisplayMode",   DEF_DISPLAY_MODE,   t_String },
  { &appear,         "appearance",    "Appearance",    DEF_APPEARANCE,     t_String },
  { &color_mode,     "colors",        "Colors",        DEF_COLORS,         t_String },
  { &view_mode,      "viewMode",      "ViewMode",      DEF_VIEW_MODE,      t_String },
  { &deform,         "deform",        "Deform",        DEF_DEFORM,         t_Bool },
  { &marks,          "marks",         "Marks",         DEF_MARKS,          t_Bool },
  { &proj,           "projection",    "Projection",    DEF_PROJECTION,     t_String },
  { &speed_x,        "speedx",        "Speedx",        DEF_SPEEDX,         t_Float},
  { &speed_y,        "speedy",        "Speedy",        DEF_SPEEDY,         t_Float},
  { &speed_z,        "speedz",        "Speedz",        DEF_SPEEDZ,         t_Float},
  { &walk_direction, "walkDirection", "WalkDirection", DEF_WALK_DIRECTION, t_Float},
  { &walk_speed,     "walkSpeed",     "WalkSpeed",     DEF_WALK_SPEED,     t_Float},
  { &deform_speed,   "deformSpeed",   "DeformSpeed",   DEF_DEFORM_SPEED,   t_Float},
  { &init_deform,    "initDeform",    "InitDeform",    DEF_INIT_DEFORM,    t_Float },
  { &surface_order,  "surfaceOrder",  "SurfaceOrder",  DEF_SURFACE_ORDER,  t_Int }
};

ENTRYPOINT ModeSpecOpt romanboy_opts =
{sizeof opts / sizeof opts[0], opts, sizeof vars / sizeof vars[0], vars, NULL};


/* Offset by which we walk above the projective plane */
#define DELTAY  0.01

/* Number of subdivisions of the projective plane */
#define NUMU 64
#define NUMV 128

/* Number of subdivisions per band */
#define NUMB 8


typedef struct {
  GLint WindH, WindW;
  GLXContext *glx_context;
  /* 3D rotation angles */
  float alpha, beta, delta;
  /* Movement parameters */
  float umove, vmove, dumove, dvmove;
  int side, dir;
  /* Deformation parameters */
  float dd;
  int defdir;
  /* The type of the generalized Roman-Boy surface */
  int g;
  /* The viewing offset in 3d */
  float offset3d[3];
  /* The 3d coordinates of the projective plane and their derivatives */
  float *pp;
  float *pn;
  /* The precomputed colors of the projective plane */
  float *col;
  /* The precomputed texture coordinates of the projective plane */
  float *tex;
  /* The "curlicue" texture */
  GLuint tex_name;
  /* Aspect ratio of the current window */
  float aspect;
  /* Trackball states */
  trackball_state *trackball;
  Bool button_pressed;
  /* A random factor to modify the rotation speeds */
  float speed_scale;
} romanboystruct;

static romanboystruct *romanboy = (romanboystruct *) NULL;


/* Add a rotation around the x-axis to the matrix m. */
static void rotatex(float m[3][3], float phi)
{
  float c, s, u, v;
  int i;

  phi *= M_PI/180.0;
  c = cos(phi);
  s = sin(phi);
  for (i=0; i<3; i++)
  {
    u = m[i][1];
    v = m[i][2];
    m[i][1] = c*u+s*v;
    m[i][2] = -s*u+c*v;
  }
}


/* Add a rotation around the y-axis to the matrix m. */
static void rotatey(float m[3][3], float phi)
{
  float c, s, u, v;
  int i;

  phi *= M_PI/180.0;
  c = cos(phi);
  s = sin(phi);
  for (i=0; i<3; i++)
  {
    u = m[i][0];
    v = m[i][2];
    m[i][0] = c*u-s*v;
    m[i][2] = s*u+c*v;
  }
}


/* Add a rotation around the z-axis to the matrix m. */
static void rotatez(float m[3][3], float phi)
{
  float c, s, u, v;
  int i;

  phi *= M_PI/180.0;
  c = cos(phi);
  s = sin(phi);
  for (i=0; i<3; i++)
  {
    u = m[i][0];
    v = m[i][1];
    m[i][0] = c*u+s*v;
    m[i][1] = -s*u+c*v;
  }
}


/* Compute the rotation matrix m from the rotation angles. */
static void rotateall(float al, float be, float de, float m[3][3])
{
  int i, j;

  for (i=0; i<3; i++)
    for (j=0; j<3; j++)
      m[i][j] = (i==j);
  rotatex(m,al);
  rotatey(m,be);
  rotatez(m,de);
}


/* Multiply two rotation matrices: o=m*n. */
static void mult_rotmat(float m[3][3], float n[3][3], float o[3][3])
{
  int i, j, k;

  for (i=0; i<3; i++)
  {
    for (j=0; j<3; j++)
    {
      o[i][j] = 0.0;
      for (k=0; k<3; k++)
        o[i][j] += m[i][k]*n[k][j];
    }
  }
}


/* Compute a 3D rotation matrix from a unit quaternion. */
static void quat_to_rotmat(float p[4], float m[3][3])
{
  double al, be, de;
  double r00, r01, r02, r12, r22;

  r00 = 1.0-2.0*(p[1]*p[1]+p[2]*p[2]);
  r01 = 2.0*(p[0]*p[1]+p[2]*p[3]);
  r02 = 2.0*(p[2]*p[0]-p[1]*p[3]);
  r12 = 2.0*(p[1]*p[2]+p[0]*p[3]);
  r22 = 1.0-2.0*(p[1]*p[1]+p[0]*p[0]);

  al = atan2(-r12,r22)*180.0/M_PI;
  be = atan2(r02,sqrt(r00*r00+r01*r01))*180.0/M_PI;
  de = atan2(-r01,r00)*180.0/M_PI;

  rotateall(al,be,de,m);
}


/* Compute a fully saturated and bright color based on an angle. */
static void color(double angle, float col[4])
{
  int s;
  double t;

  if (colors == COLORS_TWOSIDED)
    return;

  if (angle >= 0.0)
    angle = fmod(angle,2.0*M_PI);
  else
    angle = fmod(angle,-2.0*M_PI);
  s = floor(angle/(M_PI/3));
  t = angle/(M_PI/3)-s;
  if (s >= 6)
    s = 0;
  switch (s)
  {
    case 0:
      col[0] = 1.0;
      col[1] = t;
      col[2] = 0.0;
      break;
    case 1:
      col[0] = 1.0-t;
      col[1] = 1.0;
      col[2] = 0.0;
      break;
    case 2:
      col[0] = 0.0;
      col[1] = 1.0;
      col[2] = t;
      break;
    case 3:
      col[0] = 0.0;
      col[1] = 1.0-t;
      col[2] = 1.0;
      break;
    case 4:
      col[0] = t;
      col[1] = 0.0;
      col[2] = 1.0;
      break;
    case 5:
      col[0] = 1.0;
      col[1] = 0.0;
      col[2] = 1.0-t;
      break;
  }
  if (display_mode == DISP_TRANSPARENT)
    col[3] = 0.7;
  else
    col[3] = 1.0;
}


/* Set up the projective plane colors and texture. */
static void setup_roman_boy_color_texture(ModeInfo *mi, double umin,
                                          double umax, double vmin,
                                          double vmax, int numu, int numv)
{
  int i, j, k, g;
  double u, v, ur, vr;
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  g = pp->g;
  ur = umax-umin;
  vr = vmax-vmin;
  for (i=0; i<=numv; i++)
  {
    for (j=0; j<=numu; j++)
    {
      k = i*(numu+1)+j;
      if (appearance != APPEARANCE_DIRECTION_BANDS)
        u = -ur*j/numu+umin;
      else
        u = ur*j/numu+umin;
      v = vr*i/numv+vmin;
      if (colors == COLORS_DIRECTION)
        color(2.0*M_PI-fmod(2.0*u,2.0*M_PI),&pp->col[4*k]);
      else /* colors == COLORS_DISTANCE */
        color(v*(5.0/6.0),&pp->col[4*k]);
      pp->tex[2*k+0] = -16*g*u/(2.0*M_PI);
      if (appearance == APPEARANCE_DISTANCE_BANDS)
        pp->tex[2*k+1] = 32*v/(2.0*M_PI)-0.5;
      else
        pp->tex[2*k+1] = 32*v/(2.0*M_PI);
    }
  }
}


/* Draw a 3d immersion of the projective plane. */
static int roman_boy(ModeInfo *mi, double umin, double umax,
                     double vmin, double vmax, int numu, int numv)
{
  int polys = 0;
  static const GLfloat mat_diff_red[]         = { 1.0, 0.0, 0.0, 1.0 };
  static const GLfloat mat_diff_green[]       = { 0.0, 1.0, 0.0, 1.0 };
  static const GLfloat mat_diff_trans_red[]   = { 1.0, 0.0, 0.0, 0.7 };
  static const GLfloat mat_diff_trans_green[] = { 0.0, 1.0, 0.0, 0.7 };
  float p[3], pu[3], pv[3], pm[3], n[3], b[3], mat[3][3];
  int i, j, k, l, m, o, g;
  double u, v, ur, vr, oz;
  double xx[3], xxu[3], xxv[3];
  double r, s, t;
  double d, dd, radius;
  double cu, su, cgu, sgu, cgm1u, sgm1u, cv, c2v, s2v, cv2;
  double sqrt2og, h1m1og, gm1, nomx, nomy, nomux, nomuy, nomvx, nomvy;
  double den, den2, denu, denv;
  float qu[4], r1[3][3], r2[3][3];
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  g = pp->g;
  dd = pp->dd;
  d = ((6.0*dd-15.0)*dd+10.0)*dd*dd*dd;
  r = 1.0+d*d*(1.0/2.0+d*d*(1.0/6.0+d*d*(1.0/3.0)));
  radius = 1.0/r;
  oz = 0.5*r;
  if (view == VIEW_WALK)
  {
    u = pp->umove;
    v = pp->vmove;
    if (g & 1)
      v = 0.5*M_PI-0.25*v;
    else
      v = 0.5*M_PI-0.5*v;
    sqrt2og = M_SQRT2/g;
    h1m1og = 0.5*(1.0-1.0/g);
    gm1 = g-1.0;
    cu = cos(u);
    su = sin(u);
    cgu = cos(g*u);
    sgu = sin(g*u);
    cgm1u = cos(gm1*u);
    sgm1u = sin(gm1*u);
    cv = cos(v);
    c2v = cos(2.0*v);
    s2v = sin(2.0*v);
    cv2 = cv*cv;
    nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
    nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
    nomux = -sqrt2og*cv2*gm1*sgm1u-h1m1og*s2v*su;
    nomuy = sqrt2og*cv2*gm1*cgm1u-h1m1og*s2v*cu;
    nomvx = -sqrt2og*s2v*cgm1u+2.0*h1m1og*c2v*cu;
    nomvy = -sqrt2og*s2v*sgm1u-2.0*h1m1og*c2v*su;
    den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
    den2 = den*den;
    denu = 0.5*M_SQRT2*d*g*cgu*s2v;
    denv = M_SQRT2*d*sgu*c2v;
    xx[0] = nomx*den;
    xx[1] = nomy*den;
    xx[2] = cv2*den-oz;
    /* Avoid degenerate tangential plane basis vectors. */
    if (0.5*M_PI-fabs(v) < FLT_EPSILON)
    {
      if (0.5*M_PI-v < FLT_EPSILON)
        v = 0.5*M_PI-FLT_EPSILON;
      else
        v = -0.5*M_PI+FLT_EPSILON;
      cv = cos(v);
      c2v = cos(2.0*v);
      s2v = sin(2.0*v);
      cv2 = cv*cv;
      nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
      nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
      nomux = -sqrt2og*cv2*gm1*sgm1u-h1m1og*s2v*su;
      nomuy = sqrt2og*cv2*gm1*cgm1u-h1m1og*s2v*cu;
      nomvx = -sqrt2og*s2v*cgm1u+2.0*h1m1og*c2v*cu;
      nomvy = -sqrt2og*s2v*sgm1u-2.0*h1m1og*c2v*su;
      den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
      den2 = den*den;
      denu = 0.5*M_SQRT2*d*g*cgu*s2v;
      denv = M_SQRT2*d*sgu*c2v;
    }
    xxu[0] = nomux*den+nomx*denu*den2;
    xxu[1] = nomuy*den+nomy*denu*den2;
    xxu[2] = cv2*denu*den2;
    xxv[0] = nomvx*den+nomx*denv*den2;
    xxv[1] = nomvy*den+nomy*denv*den2;
    xxv[2] = -s2v*den+cv2*denv*den2;
    for (l=0; l<3; l++)
    {
      p[l] = xx[l]*radius;
      pu[l] = xxu[l]*radius;
      pv[l] = xxv[l]*radius;
    }
    n[0] = pu[1]*pv[2]-pu[2]*pv[1];
    n[1] = pu[2]*pv[0]-pu[0]*pv[2];
    n[2] = pu[0]*pv[1]-pu[1]*pv[0];
    t = 1.0/(pp->side*4.0*sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]));
    n[0] *= t;
    n[1] *= t;
    n[2] *= t;
    pm[0] = pu[0]*pp->dumove-pv[0]*0.25*pp->dvmove;
    pm[1] = pu[1]*pp->dumove-pv[1]*0.25*pp->dvmove;
    pm[2] = pu[2]*pp->dumove-pv[2]*0.25*pp->dvmove;
    t = 1.0/(4.0*sqrt(pm[0]*pm[0]+pm[1]*pm[1]+pm[2]*pm[2]));
    pm[0] *= t;
    pm[1] *= t;
    pm[2] *= t;
    b[0] = n[1]*pm[2]-n[2]*pm[1];
    b[1] = n[2]*pm[0]-n[0]*pm[2];
    b[2] = n[0]*pm[1]-n[1]*pm[0];
    t = 1.0/(4.0*sqrt(b[0]*b[0]+b[1]*b[1]+b[2]*b[2]));
    b[0] *= t;
    b[1] *= t;
    b[2] *= t;

    /* Compute alpha, beta, gamma from the three basis vectors.
           |  -b[0]  -b[1]  -b[2] |
       m = |   n[0]   n[1]   n[2] |
           | -pm[0] -pm[1] -pm[2] |
    */
    pp->alpha = atan2(-n[2],-pm[2])*180/M_PI;
    pp->beta = atan2(-b[2],sqrt(b[0]*b[0]+b[1]*b[1]))*180/M_PI;
    pp->delta = atan2(b[1],-b[0])*180/M_PI;

    /* Compute the rotation that rotates the projective plane in 3D. */
    rotateall(pp->alpha,pp->beta,pp->delta,mat);

    u = pp->umove;
    v = pp->vmove;
    if (g & 1)
      v = 0.5*M_PI-0.25*v;
    else
      v = 0.5*M_PI-0.5*v;
    sqrt2og = M_SQRT2/g;
    h1m1og = 0.5*(1.0-1.0/g);
    gm1 = g-1.0;
    cu = cos(u);
    su = sin(u);
    sgu = sin(g*u);
    cgm1u = cos(gm1*u);
    sgm1u = sin(gm1*u);
    cv = cos(v);
    s2v = sin(2.0*v);
    cv2 = cv*cv;
    nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
    nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
    den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
    xx[0] = nomx*den;
    xx[1] = nomy*den;
    xx[2] = cv2*den-oz;
    for (l=0; l<3; l++)
    {
      r = 0.0;
      for (m=0; m<3; m++)
        r += mat[l][m]*xx[m];
      p[l] = r*radius;
    }

    pp->offset3d[0] = -p[0];
    pp->offset3d[1] = -p[1]-DELTAY;
    pp->offset3d[2] = -p[2];
  }
  else
  {
    /* Compute the rotation that rotates the projective plane in 3D,
       including the trackball rotations. */
    rotateall(pp->alpha,pp->beta,pp->delta,r1);

    gltrackball_get_quaternion(pp->trackball,qu);
    quat_to_rotmat(qu,r2);

    mult_rotmat(r2,r1,mat);
  }

  if (colors == COLORS_TWOSIDED)
  {
    glColor3fv(mat_diff_red);
    if (display_mode == DISP_TRANSPARENT)
    {
      glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_diff_trans_red);
      glMaterialfv(GL_BACK,GL_AMBIENT_AND_DIFFUSE,mat_diff_trans_green);
    }
    else
    {
      glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,mat_diff_red);
      glMaterialfv(GL_BACK,GL_AMBIENT_AND_DIFFUSE,mat_diff_green);
    }
  }
  glBindTexture(GL_TEXTURE_2D,pp->tex_name);

  ur = umax-umin;
  vr = vmax-vmin;

  /* Set up the projective plane coordinates and normals. */
  if (appearance != APPEARANCE_DIRECTION_BANDS)
  {
    for (i=0; i<=numv; i++)
    {
      if (appearance == APPEARANCE_DISTANCE_BANDS &&
          ((i & (NUMB-1)) >= NUMB/4+1) && ((i & (NUMB-1)) < 3*NUMB/4))
        continue;
      for (j=0; j<=numu; j++)
      {
        o = i*(numu+1)+j;
        u = ur*j/numu+umin;
        v = vr*i/numv+vmin;
        if (g & 1)
          v = 0.5*M_PI-0.25*v;
        else
          v = 0.5*M_PI-0.5*v;
        sqrt2og = M_SQRT2/g;
        h1m1og = 0.5*(1.0-1.0/g);
        gm1 = g-1.0;
        cu = cos(u);
        su = sin(u);
        cgu = cos(g*u);
        sgu = sin(g*u);
        cgm1u = cos(gm1*u);
        sgm1u = sin(gm1*u);
        cv = cos(v);
        c2v = cos(2.0*v);
        s2v = sin(2.0*v);
        cv2 = cv*cv;
        nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
        nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
        nomux = -sqrt2og*cv2*gm1*sgm1u-h1m1og*s2v*su;
        nomuy = sqrt2og*cv2*gm1*cgm1u-h1m1og*s2v*cu;
        nomvx = -sqrt2og*s2v*cgm1u+2.0*h1m1og*c2v*cu;
        nomvy = -sqrt2og*s2v*sgm1u-2.0*h1m1og*c2v*su;
        den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
        den2 = den*den;
        denu = 0.5*M_SQRT2*d*g*cgu*s2v;
        denv = M_SQRT2*d*sgu*c2v;
        xx[0] = nomx*den;
        xx[1] = nomy*den;
        xx[2] = cv2*den-oz;
        /* Avoid degenerate tangential plane basis vectors. */
        if (0.5*M_PI-fabs(v) < FLT_EPSILON)
        {
          if (0.5*M_PI-v < FLT_EPSILON)
            v = 0.5*M_PI-FLT_EPSILON;
          else
            v = -0.5*M_PI+FLT_EPSILON;
          cv = cos(v);
          c2v = cos(2.0*v);
          s2v = sin(2.0*v);
          cv2 = cv*cv;
          nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
          nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
          nomux = -sqrt2og*cv2*gm1*sgm1u-h1m1og*s2v*su;
          nomuy = sqrt2og*cv2*gm1*cgm1u-h1m1og*s2v*cu;
          nomvx = -sqrt2og*s2v*cgm1u+2.0*h1m1og*c2v*cu;
          nomvy = -sqrt2og*s2v*sgm1u-2.0*h1m1og*c2v*su;
          den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
          den2 = den*den;
          denu = 0.5*M_SQRT2*d*g*cgu*s2v;
          denv = M_SQRT2*d*sgu*c2v;
        }
        xxu[0] = nomux*den+nomx*denu*den2;
        xxu[1] = nomuy*den+nomy*denu*den2;
        xxu[2] = cv2*denu*den2;
        xxv[0] = nomvx*den+nomx*denv*den2;
        xxv[1] = nomvy*den+nomy*denv*den2;
        xxv[2] = -s2v*den+cv2*denv*den2;
        for (l=0; l<3; l++)
        {
          r = 0.0;
          s = 0.0;
          t = 0.0;
          for (m=0; m<3; m++)
          {
            r += mat[l][m]*xx[m];
            s += mat[l][m]*xxu[m];
            t += mat[l][m]*xxv[m];
          }
          p[l] = r*radius+pp->offset3d[l];
          pu[l] = s*radius;
          pv[l] = t*radius;
        }
        n[0] = pu[1]*pv[2]-pu[2]*pv[1];
        n[1] = pu[2]*pv[0]-pu[0]*pv[2];
        n[2] = pu[0]*pv[1]-pu[1]*pv[0];
        t = 1.0/sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
        n[0] *= t;
        n[1] *= t;
        n[2] *= t;
        pp->pp[3*o+0] = p[0];
        pp->pp[3*o+1] = p[1];
        pp->pp[3*o+2] = p[2];
        pp->pn[3*o+0] = n[0];
        pp->pn[3*o+1] = n[1];
        pp->pn[3*o+2] = n[2];
      }
    }
  }
  else /* appearance == APPEARANCE_DIRECTION_BANDS */
  {
    for (j=0; j<=numu; j++)
    {
      if ((j & (NUMB-1)) >= NUMB/2+1)
        continue;
      for (i=0; i<=numv; i++)
      {
        o = i*(numu+1)+j;
        u = -ur*j/numu+umin;
        v = vr*i/numv+vmin;
        if (g & 1)
          v = 0.5*M_PI-0.25*v;
        else
          v = 0.5*M_PI-0.5*v;
        sqrt2og = M_SQRT2/g;
        h1m1og = 0.5*(1.0-1.0/g);
        gm1 = g-1.0;
        cu = cos(u);
        su = sin(u);
        cgu = cos(g*u);
        sgu = sin(g*u);
        cgm1u = cos(gm1*u);
        sgm1u = sin(gm1*u);
        cv = cos(v);
        c2v = cos(2.0*v);
        s2v = sin(2.0*v);
        cv2 = cv*cv;
        nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
        nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
        nomux = -sqrt2og*cv2*gm1*sgm1u-h1m1og*s2v*su;
        nomuy = sqrt2og*cv2*gm1*cgm1u-h1m1og*s2v*cu;
        nomvx = -sqrt2og*s2v*cgm1u+2.0*h1m1og*c2v*cu;
        nomvy = -sqrt2og*s2v*sgm1u-2.0*h1m1og*c2v*su;
        den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
        den2 = den*den;
        denu = 0.5*M_SQRT2*d*g*cgu*s2v;
        denv = M_SQRT2*d*sgu*c2v;
        xx[0] = nomx*den;
        xx[1] = nomy*den;
        xx[2] = cv2*den-oz;
        /* Avoid degenerate tangential plane basis vectors. */
        if (0.5*M_PI-fabs(v) < FLT_EPSILON)
        {
          if (0.5*M_PI-v < FLT_EPSILON)
            v = 0.5*M_PI-FLT_EPSILON;
          else
            v = -0.5*M_PI+FLT_EPSILON;
          cv = cos(v);
          c2v = cos(2.0*v);
          s2v = sin(2.0*v);
          cv2 = cv*cv;
          nomx = sqrt2og*cv2*cgm1u+h1m1og*s2v*cu;
          nomy = sqrt2og*cv2*sgm1u-h1m1og*s2v*su;
          nomux = -sqrt2og*cv2*gm1*sgm1u-h1m1og*s2v*su;
          nomuy = sqrt2og*cv2*gm1*cgm1u-h1m1og*s2v*cu;
          nomvx = -sqrt2og*s2v*cgm1u+2.0*h1m1og*c2v*cu;
          nomvy = -sqrt2og*s2v*sgm1u-2.0*h1m1og*c2v*su;
          den = 1.0/(1.0-0.5*M_SQRT2*d*s2v*sgu);
          den2 = den*den;
          denu = 0.5*M_SQRT2*d*g*cgu*s2v;
          denv = M_SQRT2*d*sgu*c2v;
        }
        xxu[0] = nomux*den+nomx*denu*den2;
        xxu[1] = nomuy*den+nomy*denu*den2;
        xxu[2] = cv2*denu*den2;
        xxv[0] = nomvx*den+nomx*denv*den2;
        xxv[1] = nomvy*den+nomy*denv*den2;
        xxv[2] = -s2v*den+cv2*denv*den2;
        for (l=0; l<3; l++)
        {
          r = 0.0;
          s = 0.0;
          t = 0.0;
          for (m=0; m<3; m++)
          {
            r += mat[l][m]*xx[m];
            s += mat[l][m]*xxu[m];
            t += mat[l][m]*xxv[m];
          }
          p[l] = r*radius+pp->offset3d[l];
          pu[l] = s*radius;
          pv[l] = t*radius;
        }
        n[0] = pu[1]*pv[2]-pu[2]*pv[1];
        n[1] = pu[2]*pv[0]-pu[0]*pv[2];
        n[2] = pu[0]*pv[1]-pu[1]*pv[0];
        t = 1.0/sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
        n[0] *= t;
        n[1] *= t;
        n[2] *= t;
        pp->pp[3*o+0] = p[0];
        pp->pp[3*o+1] = p[1];
        pp->pp[3*o+2] = p[2];
        pp->pn[3*o+0] = n[0];
        pp->pn[3*o+1] = n[1];
        pp->pn[3*o+2] = n[2];
      }
    }
  }

  if (appearance != APPEARANCE_DIRECTION_BANDS)
  {
    for (i=0; i<numv; i++)
    {
      if (appearance == APPEARANCE_DISTANCE_BANDS &&
          ((i & (NUMB-1)) >= NUMB/4) && ((i & (NUMB-1)) < 3*NUMB/4))
        continue;
      if (display_mode == DISP_WIREFRAME)
        glBegin(GL_QUAD_STRIP);
      else
        glBegin(GL_TRIANGLE_STRIP);
      for (j=0; j<=numu; j++)
      {
        for (k=0; k<=1; k++)
        {
          l = (i+k);
          m = j;
          o = l*(numu+1)+m;
          glTexCoord2fv(&pp->tex[2*o]);
          if (colors != COLORS_TWOSIDED)
          {
            glColor3fv(&pp->col[4*o]);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,
                         &pp->col[4*o]);
          }
          glNormal3fv(&pp->pn[3*o]);
          glVertex3fv(&pp->pp[3*o]);
          polys++;
        }
      }
      glEnd();
    }
  }
  else /* appearance == APPEARANCE_DIRECTION_BANDS */
  {
    for (j=0; j<numu; j++)
    {
      if ((j & (NUMB-1)) >= NUMB/2)
        continue;
      if (display_mode == DISP_WIREFRAME)
        glBegin(GL_QUAD_STRIP);
      else
        glBegin(GL_TRIANGLE_STRIP);
      for (i=0; i<=numv; i++)
      {
        for (k=0; k<=1; k++)
        {
          l = i;
          m = (j+k);
          o = l*(numu+1)+m;
          glTexCoord2fv(&pp->tex[2*o]);
          if (colors != COLORS_TWOSIDED)
          {
            glColor3fv(&pp->col[4*o]);
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,
                         &pp->col[4*o]);
          }
          glNormal3fv(&pp->pn[3*o]);
          glVertex3fv(&pp->pp[3*o]);
          polys++;
        }
      }
      glEnd();
    }
  }

  polys /= 2;
  return polys;
}


/* Generate a texture image that shows the orientation reversal. */
static void gen_texture(ModeInfo *mi)
{
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  glGenTextures(1,&pp->tex_name);
  glBindTexture(GL_TEXTURE_2D,pp->tex_name);
  glPixelStorei(GL_UNPACK_ALIGNMENT,1);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,TEX_DIMENSION,TEX_DIMENSION,0,
               GL_LUMINANCE,GL_UNSIGNED_BYTE,texture);
}


static void init(ModeInfo *mi)
{
  static const GLfloat light_ambient[]  = { 0.0, 0.0, 0.0, 1.0 };
  static const GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
  static const GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  static const GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
  static const GLfloat mat_specular[]   = { 1.0, 1.0, 1.0, 1.0 };
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  if (deform_speed == 0.0)
    deform_speed = 10.0;

  if (init_deform < 0.0)
    init_deform = 0.0;
  if (init_deform > 1000.0)
    init_deform = 1000.0;

  if (walk_speed == 0.0)
    walk_speed = 20.0;

  if (view == VIEW_TURN)
  {
    pp->alpha = frand(360.0);
    pp->beta = frand(360.0);
    pp->delta = frand(360.0);
  }
  else
  {
    pp->alpha = 0.0;
    pp->beta = 0.0;
    pp->delta = 0.0;
  }
  pp->umove = frand(2.0*M_PI);
  pp->vmove = frand(2.0*M_PI);
  pp->dumove = 0.0;
  pp->dvmove = 0.0;
  pp->side = 1;
  if (sin(walk_direction*M_PI/180.0) >= 0.0)
    pp->dir = 1;
  else
    pp->dir = -1;

  pp->dd = init_deform*0.001;
  pp->defdir = -1;

  pp->offset3d[0] = 0.0;
  pp->offset3d[1] = 0.0;
  pp->offset3d[2] = -1.8;

  gen_texture(mi);
  setup_roman_boy_color_texture(mi,0.0,2.0*M_PI,0.0,2.0*M_PI,pp->g*NUMU,NUMV);

  if (marks)
    glEnable(GL_TEXTURE_2D);
  else
    glDisable(GL_TEXTURE_2D);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection == DISP_PERSPECTIVE || view == VIEW_WALK)
  {
    if (view == VIEW_WALK)
      gluPerspective(60.0,1.0,0.01,10.0);
    else
      gluPerspective(60.0,1.0,0.1,10.0);
  }
  else
  {
    glOrtho(-1.0,1.0,-1.0,1.0,0.1,10.0);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

# ifdef HAVE_JWZGLES /* #### glPolygonMode other than GL_FILL unimplemented */
  if (display_mode == DISP_WIREFRAME)
    display_mode = DISP_SURFACE;
# endif

  if (display_mode == DISP_SURFACE)
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50.0);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
  else if (display_mode == DISP_TRANSPARENT)
  {
    glDisable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,50.0);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  }
  else  /* display_mode == DISP_WIREFRAME */
  {
    glDisable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_BLEND);
  }
}


/* Redisplay the Klein bottle. */
static void display_romanboy(ModeInfo *mi)
{
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  if (!pp->button_pressed)
  {
    if (deform)
    {
      pp->dd += pp->defdir*deform_speed*0.001;
      if (pp->dd < 0.0)
      {
        pp->dd = -pp->dd;
        pp->defdir = -pp->defdir;
      }
      if (pp->dd > 1.0)
      {
        pp->dd = 2.0-pp->dd;
        pp->defdir = -pp->defdir;
      }
    }
    if (view == VIEW_TURN)
    {
      pp->alpha += speed_x * pp->speed_scale;
      if (pp->alpha >= 360.0)
        pp->alpha -= 360.0;
      pp->beta += speed_y * pp->speed_scale;
      if (pp->beta >= 360.0)
        pp->beta -= 360.0;
      pp->delta += speed_z * pp->speed_scale;
      if (pp->delta >= 360.0)
        pp->delta -= 360.0;
    }
    if (view == VIEW_WALK)
    {
      pp->dvmove = (pp->dir*sin(walk_direction*M_PI/180.0)*
                    walk_speed*M_PI/4096.0);
      pp->vmove += pp->dvmove;
      if (pp->vmove > 2.0*M_PI)
      {
        pp->vmove = 4.0*M_PI-pp->vmove;
        pp->umove = pp->umove-M_PI;
        if (pp->umove < 0.0)
          pp->umove += 2.0*M_PI;
        pp->side = -pp->side;
        pp->dir = -pp->dir;
        pp->dvmove = -pp->dvmove;
      }
      if (pp->vmove < 0.0)
      {
        pp->vmove = -pp->vmove;
        pp->umove = pp->umove-M_PI;
        if (pp->umove < 0.0)
          pp->umove += 2.0*M_PI;
        pp->dir = -pp->dir;
        pp->dvmove = -pp->dvmove;
      }
      pp->dumove = cos(walk_direction*M_PI/180.0)*walk_speed*M_PI/4096.0;
      pp->umove += pp->dumove;
      if (pp->umove >= 2.0*M_PI)
        pp->umove -= 2.0*M_PI;
      if (pp->umove < 0.0)
        pp->umove += 2.0*M_PI;
    }
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection == DISP_PERSPECTIVE || view == VIEW_WALK)
  {
    if (view == VIEW_WALK)
      gluPerspective(60.0,pp->aspect,0.01,10.0);
    else
      gluPerspective(60.0,pp->aspect,0.1,10.0);
  }
  else
  {
    if (pp->aspect >= 1.0)
      glOrtho(-pp->aspect,pp->aspect,-1.0,1.0,0.1,10.0);
    else
      glOrtho(-1.0,1.0,-1.0/pp->aspect,1.0/pp->aspect,0.1,10.0);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  mi->polygon_count = roman_boy(mi,0.0,2.0*M_PI,0.0,2.0*M_PI,pp->g*NUMU,NUMV);
}


ENTRYPOINT void reshape_romanboy(ModeInfo *mi, int width, int height)
{
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  pp->WindW = (GLint)width;
  pp->WindH = (GLint)height;
  glViewport(0,0,width,height);
  pp->aspect = (GLfloat)width/(GLfloat)height;
}


ENTRYPOINT Bool romanboy_handle_event(ModeInfo *mi, XEvent *event)
{
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  if (event->xany.type == ButtonPress && event->xbutton.button == Button1)
  {
    pp->button_pressed = True;
    gltrackball_start(pp->trackball, event->xbutton.x, event->xbutton.y,
                      MI_WIDTH(mi), MI_HEIGHT(mi));
    return True;
  }
  else if (event->xany.type == ButtonRelease &&
           event->xbutton.button == Button1)
  {
    pp->button_pressed = False;
    return True;
  }
  else if (event->xany.type == MotionNotify && pp->button_pressed)
  {
    gltrackball_track(pp->trackball, event->xmotion.x, event->xmotion.y,
                      MI_WIDTH(mi), MI_HEIGHT(mi));
    return True;
  }

  return False;
}


/*
 *-----------------------------------------------------------------------------
 *-----------------------------------------------------------------------------
 *    Xlock hooks.
 *-----------------------------------------------------------------------------
 *-----------------------------------------------------------------------------
 */

/*
 *-----------------------------------------------------------------------------
 *    Initialize romanboy.  Called each time the window changes.
 *-----------------------------------------------------------------------------
 */

ENTRYPOINT void init_romanboy(ModeInfo *mi)
{
  romanboystruct *pp;

  if (romanboy == NULL)
  {
    romanboy =
      (romanboystruct *)calloc(MI_NUM_SCREENS(mi),sizeof(romanboystruct));
    if (romanboy == NULL)
      return;
  }
  pp = &romanboy[MI_SCREEN(mi)];

  if (surface_order < 2)
    pp->g = 2;
  else if (surface_order > 9)
    pp->g = 9;
  else
    pp->g = surface_order;

  pp->pp = calloc(3*pp->g*(NUMU+1)*(NUMV+1),sizeof(float));
  pp->pn = calloc(3*pp->g*(NUMU+1)*(NUMV+1),sizeof(float));
  pp->col = calloc(4*pp->g*(NUMU+1)*(NUMV+1),sizeof(float));
  pp->tex = calloc(2*pp->g*(NUMU+1)*(NUMV+1),sizeof(float));

  pp->trackball = gltrackball_init(True);
  pp->button_pressed = False;

  /* Set the display mode. */
  if (!strcasecmp(mode,"random"))
  {
    display_mode = random() % NUM_DISPLAY_MODES;
  }
  else if (!strcasecmp(mode,"wireframe"))
  {
    display_mode = DISP_WIREFRAME;
  }
  else if (!strcasecmp(mode,"surface"))
  {
    display_mode = DISP_SURFACE;
  }
  else if (!strcasecmp(mode,"transparent"))
  {
    display_mode = DISP_TRANSPARENT;
  }
  else
  {
    display_mode = random() % NUM_DISPLAY_MODES;
  }

  /* Orientation marks don't make sense in wireframe mode. */
  if (display_mode == DISP_WIREFRAME)
    marks = False;

  /* Set the appearance. */
  if (!strcasecmp(appear,"random"))
  {
    appearance = random() % NUM_APPEARANCES;
  }
  else if (!strcasecmp(appear,"solid"))
  {
    appearance = APPEARANCE_SOLID;
  }
  else if (!strcasecmp(appear,"distance-bands"))
  {
    appearance = APPEARANCE_DISTANCE_BANDS;
  }
  else if (!strcasecmp(appear,"direction-bands"))
  {
    appearance = APPEARANCE_DIRECTION_BANDS;
  }
  else
  {
    appearance = random() % NUM_APPEARANCES;
  }

  /* Set the color mode. */
  if (!strcasecmp(color_mode,"random"))
  {
    colors = random() % NUM_COLORS;
  }
  else if (!strcasecmp(color_mode,"two-sided"))
  {
    colors = COLORS_TWOSIDED;
  }
  else if (!strcasecmp(color_mode,"distance"))
  {
    colors = COLORS_DISTANCE;
  }
  else if (!strcasecmp(color_mode,"direction"))
  {
    colors = COLORS_DIRECTION;
  }
  else
  {
    colors = random() % NUM_COLORS;
  }

  /* Set the view mode. */
  if (!strcasecmp(view_mode,"random"))
  {
    view = random() % NUM_VIEW_MODES;
  }
  else if (!strcasecmp(view_mode,"walk"))
  {
    view = VIEW_WALK;
  }
  else if (!strcasecmp(view_mode,"turn"))
  {
    view = VIEW_TURN;
  }
  else
  {
    view = random() % NUM_VIEW_MODES;
  }

  /* Set the 3d projection mode. */
  if (!strcasecmp(proj,"random"))
  {
    /* Orthographic projection only makes sense in turn mode. */
    if (view == VIEW_TURN)
      projection = random() % NUM_DISP_MODES;
    else
      projection = DISP_PERSPECTIVE;
  }
  else if (!strcasecmp(proj,"perspective"))
  {
    projection = DISP_PERSPECTIVE;
  }
  else if (!strcasecmp(proj,"orthographic"))
  {
    projection = DISP_ORTHOGRAPHIC;
  }
  else
  {
    /* Orthographic projection only makes sense in turn mode. */
    if (view == VIEW_TURN)
      projection = random() % NUM_DISP_MODES;
    else
      projection = DISP_PERSPECTIVE;
  }

  /* make multiple screens rotate at slightly different rates. */
  pp->speed_scale = 0.9 + frand(0.3);

  if ((pp->glx_context = init_GL(mi)) != NULL)
  {
    reshape_romanboy(mi,MI_WIDTH(mi),MI_HEIGHT(mi));
    glDrawBuffer(GL_BACK);
    init(mi);
  }
  else
  {
    MI_CLEARWINDOW(mi);
  }
}

/*
 *-----------------------------------------------------------------------------
 *    Called by the mainline code periodically to update the display.
 *-----------------------------------------------------------------------------
 */
ENTRYPOINT void draw_romanboy(ModeInfo *mi)
{
  Display *display = MI_DISPLAY(mi);
  Window window = MI_WINDOW(mi);
  romanboystruct *pp;

  if (romanboy == NULL)
    return;
  pp = &romanboy[MI_SCREEN(mi)];

  MI_IS_DRAWN(mi) = True;
  if (!pp->glx_context)
    return;

  glXMakeCurrent(display,window,*(pp->glx_context));

  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  display_romanboy(mi);

  if (MI_IS_FPS(mi))
    do_fps (mi);

  glFlush();

  glXSwapBuffers(display,window);
}


/*
 *-----------------------------------------------------------------------------
 *    The display is being taken away from us.  Free up malloc'ed 
 *      memory and X resources that we've alloc'ed.  Only called
 *      once, we must zap everything for every screen.
 *-----------------------------------------------------------------------------
 */

ENTRYPOINT void release_romanboy(ModeInfo *mi)
{
  if (romanboy != NULL)
  {
    int screen;

    for (screen = 0; screen < MI_NUM_SCREENS(mi); screen++)
    {
      romanboystruct *pp = &romanboy[screen];

      if (pp->glx_context)
        pp->glx_context = (GLXContext *)NULL;
      if (pp->pp)
        (void) free((void *)pp->pp);
      if (pp->pn)
        (void) free((void *)pp->pn);
      if (pp->col)
        (void) free((void *)pp->col);
      if (pp->tex)
        (void) free((void *)pp->tex);
    }
    (void) free((void *)romanboy);
    romanboy = (romanboystruct *)NULL;
  }
  FreeAllGL(mi);
}

#ifndef STANDALONE
ENTRYPOINT void change_romanboy(ModeInfo *mi)
{
  romanboystruct *pp = &romanboy[MI_SCREEN(mi)];

  if (!pp->glx_context)
    return;

  glXMakeCurrent(MI_DISPLAY(mi),MI_WINDOW(mi),*(pp->glx_context));
  init(mi);
}
#endif /* !STANDALONE */

XSCREENSAVER_MODULE ("RomanBoy", romanboy)

#endif /* USE_GL */
