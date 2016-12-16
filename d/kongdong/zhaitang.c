//1997-3-10 by qyz
#include <room.h>

inherit ROOM;


void create()
{
	set("short","斋堂");
	set("long",@LONG
这里就是斋堂，是崆峒弟子和进香客用膳的地方，内有一口炼丹时用的长生
井，井深丈许，宽约二尺，井水长年不枯，据传饮此水可以长生，因此要用一两
黄金才能在这里打一次水，斋堂的一角立着数口大灶，几个小道士在烧火，忙着
做斋饭，另一角放了许多素菜，是崆峒弟子在山上自己种的。
LONG);
	set("exits",
	([
          "east" : __DIR__"zhaohe_tang",
          	]));
//        set("outdoors","kongdong");
set("need_clean", "崆峒派");
	set("objects",([
		__DIR__"npc/kdizi5" : 1,
                __DIR__"npc/kdizi3" : 2,
		]) );
        setup();
        //place_program(ROOM);
}
