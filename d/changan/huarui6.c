//Room: huarui6.c

inherit ROOM;

void create ()
{
        set ("short", "华瑞街");
        set("long", @LONG
华瑞街是长安城南一条东西向的大道，也是长安城的居民区。一
条碎石子铺成的街坊，南边可见一些民居住宅，街头有炊烟袅袅飘来
青柴的香味。不远处传来家家户户舂米的声音，还有大户人家榨香油
的醇香味。
LONG );
        set("exits", 
        ([ //sizeof() == 4
                "south" : "/d/changan/minju6",
                "north" : "/d/changan/tuchangguan",
                "west" : "/d/changan/huarui5",
                "east" : "/d/changan/liande-nankou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10690);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}