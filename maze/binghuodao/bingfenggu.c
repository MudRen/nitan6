inherit __DIR__"binghuodao";

void create()
{
        set("short", "�����");
        set("long",
"������һ����Ҫ��Ͽ�ȣ�����Ͽ�ȱ���ѩ���ǣ�����ѩ������\n"
"�ǰ�ããһƬ����ʱ���������Ǻ�������ë���Ȼ��\n"
);
        set("exits", ([ 
                "east"   : __DIR__"bingfenggu2", 
                "north"   : __DIR__"bingfengzhandao",
                "south"   : __DIR__"xiagu2",
        ]));

        set("n_time", 30);
        set("n_npc",1);
        set("n_max_npc", 4);
        set("s_npc", __DIR__"npc/binglang");
        
        setup();
}
