inherit ROOM;

void create()
{
        set("short", "羊肠小路");
        set("long", @LONG
这是一条蜿蜒曲折的小路，右面是一小片低矮的树林，左面
是陡峭的山壁。地上满是乱石子，有的还很尖利，看样子这里很
少有人来。
LONG
        );
        set("exits", ([
  "southeast" : __DIR__"ycl2",
  "west" : __DIR__"ycl4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
