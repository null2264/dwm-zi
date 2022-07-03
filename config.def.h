/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx       =  2;   /* border pixel of windows */
static const int gappx                   = 15;   /* gaps between windows */
static const unsigned int snap           = 32;   /* snap pixel */
static const unsigned int systraypinning =  0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing =  4;   /* systray spacing */
static const int systraypinningfailfirst =  1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             =  1;   /* 0 means no systray */
static const int swallowfloating         =  0;   /* 1 means swallow floating windows by default */
static const int showbar                 =  1;   /* 0 means no bar */
static const int topbar                  =  1;   /* 0 means bottom bar */
static const int user_bh                 = 28;   /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]               =  {
                                             "Sarasa Term J:bold:size=10",
					     "Iosevka Nerd Font:bold:size=10:antialias=true:autohint=true",
					     "feather:size=10"
                                            };
static const char dmenufont[]            = "monospace:size=10";
static const char col_fg[]               = "#e1f3ff";
static const char col_fgD[]              = "#2f3640";
static const char col_bgTags[]           = "#2e3438";
static const char col_bg[]               = "#0e1418";
static const char col_primary[]          = "#37b0ff";
static const char col_border_Foc[]       = "#37b0ff";
static const char col_border_Nor[]       = "#2f3640";

static const char *colors[][3]           = {
	/*                    fg         bg         border   */
	[SchemeNorm]	  = { col_fg, col_bg, col_border_Nor },
	[SchemeSel]  	  = { col_fg, col_bg,  col_border_Foc },
	[SchemeStatus]    = { col_fg, col_bgTags, "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]   = { col_fg, col_primary,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_fg, col_bgTags, "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]   = { col_fg, col_bg,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_fg, col_bg, "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* sticky indicator */
static const XPoint stickyicon[]         = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb         = {4,8};	/* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	tags -> starts from 0
	 */
	/* class     instance title  tags mask	   isfloating	isterminal  noswallow  monitor */
	{ "Gimp",     NULL,   NULL,	0,            1,	 0,		1,	-1, },
	{ "PacketTracer7",     NULL,   NULL,	0,            1,	 0,		1,	-1, },
	{ "discord",  NULL,   NULL,	1 << 8,       0,         0,		0,	-1, },
	{ "qutebrowser",  NULL,   NULL,	1 << 1,       0,         0,		0,	-1, },
	{ "firefox",  NULL,   NULL,	1 << 1,       0,         0,		0,	-1, },
	{ "Waterfox",  NULL,   NULL,	1 << 1,       0,         0,		0,	-1, },
	{ "obs",      NULL,   NULL,	1 << 2,       0,         0,		0,	-1, },
	{ "Spotify",  "spotify",   NULL,	1 << 3,       0,         0,		0,	-1, },
	{ "Test-PyQT.py",  NULL,   NULL,	1 << 3,       1,         0,		0,	-1, },
	{ "st",       NULL,   NULL,     0,            0,         1,            -1,        -1 },
	{ "Alacritty",NULL,   NULL,     0,            0,         1,            -1,        -1 },
	{ "kitty",NULL,   NULL,     0,            0,         1,            -1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* first entry is default */
	/* symbol     arrange function */
	{ "(@)",      spiral },
	{ "[]=",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,   ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static char rofi_theme[] = "~/.config/rofi/theme/Android/grid.rasi";
static const char *dmenucmd[] = { "dmenu_run", "-h", "28", "-m", dmenumon, NULL };
static const char *roficmd[] = {"rofi", "-show", "drun", "-theme", rofi_theme};
static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
	/* modifier                     key		function        argument */
	/* { MODKEY,                    XK_space,  	spawn,          {.v = dmenucmd } }, */
	{ MODKEY,                       XK_space,  	spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      	togglebar,      {0} },
/*	{ MODKEY|ALTKEY,                XK_j,		focusstack,     {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_k,		focusstack,     {.i = -1 } },*/
	{ MODKEY|ShiftMask,             XK_h,		setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_l,		setgaps,        {.i = +5 } },
	{ NULL,				0x1008ff1b,	spawn,		{.v = dmenucmd } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_equal,	setgaps,	{.i = 0  } },
	STACKKEYS(MODKEY,				focus)
	STACKKEYS(MODKEY|ShiftMask,			push)
	{ MODKEY,                       XK_i,		incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,		incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,		setmfact,       {.f = +0.05} },
	{ MODKEY|ALTKEY,                XK_h,		setmfact,       {.f = -0.05} },
	{ MODKEY|ALTKEY,		XK_l,		setmfact,       {.f = +0.05} },
	/* { MODKEY,			XK_Tab,		view,           {0} }, */
	{ MODKEY,			XK_q,		killclient,     {0} },
	// --- [Start] layout changer, should always use MODKEY + Shift
	{ MODKEY|ShiftMask,             XK_s,		setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,		setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_n,		setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_Tab,		setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,		setlayout,      {.v = &layouts[4]} },
	// --- [End]
	{ MODKEY,			XK_f,		togglefloating, {0} },
	{ MODKEY,                       XK_s,		togglesticky,   {0} },
/*	{ MODKEY,                       XK_0,		view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,		tag,            {.ui = ~0 } },*/
	{ MODKEY,                       XK_comma,	focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,	tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,				0)
	TAGKEYS(                        XK_2,				1)
	TAGKEYS(                        XK_3,				2)
	TAGKEYS(                        XK_4,				3)
	TAGKEYS(                        XK_5,				4)
	TAGKEYS(                        XK_6,				5)
	TAGKEYS(                        XK_7,				6)
	TAGKEYS(                        XK_8,				7)
	TAGKEYS(                        XK_9,				8)
	TAGKEYS(                        XK_0,				9)
	{ MODKEY|ALTKEY,                XK_q,		quit,           {0} },
	{ MODKEY|ALTKEY,                XK_r,		quit,           {1} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

