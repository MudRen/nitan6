inherit __DIR__"fengd";

void create()
{
        set("short", "灌木丛");
        set("long", query_long());
        set("exits", ([
  "south" : __DIR__"fengdown5",
  "north" : __DIR__"fengd4",
  "west" : __DIR__"fengd2",
]));

        set("item_desc", ([
        "果子" : (: query_item_desc :),
        "小果子" : (: query_item_desc :),
]));
        set("outdoors", "yaowang");
        setup();
}


