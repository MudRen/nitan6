inherit DEMONROOM;

void create()
{
        set("short", "ǧ�߶�");
        set("long",@LONG
�����߶��ڵ�ǧ�߶���ֻ���������Ƕ��ߣ��ֲ��ǳ���
LONG);


        set("exits", ([
                "north"  : __DIR__"shedong4.1",                
                "south"  : __DIR__"shedong4.3",
        ]));

                set("n_time", 60);
                set("n_npc", 2); 
                set("n_max_npc", 5);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        setup();
}