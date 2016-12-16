inherit ROOM;

void create()
{
        set("short", "后殿");
        set("long", @LONG
 这里是雪山寺的后殿，也是雪山弟子闭门练功的地方。殿内是一
些练功的蒲团和木人，还有一些吊挂着的沙袋和直竖的木桩。
LONG );

        set("exits", ([
                "north" : __DIR__"chanshi",
                "south" : __DIR__"neidian",
                "east" : __DIR__"tower",
        ]));

        setup();
        replace_program(ROOM);
}