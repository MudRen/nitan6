//ROOM /d/xiakedao/dating.c

inherit ROOM;

int do_push(string arg);
void create()
{
        set("short", "����");
        set("long", @LONG
���ǡ����͵����Ĵ��������ܵ�����ţ�������������һ��
�����硣���ڰ���һ���������ӣ�������������������������º�
�Ӵ�������ȥ����������������
LONG );
//        set("valid_startroom",1);
        set("no_fight","1");
        set("item_desc",([
                "pingfeng" : "����һ������ʯ�������磬�ǳ�Ư����Ҳ���������ְ�����(push)����\n",
        ]));
        set("exits", ([
                "north" : __DIR__"shidong5",
                "east"  : __DIR__"shufang",
                "west"  : __DIR__"wuqiku",
        ]));
        set("objects",([
                __DIR__"npc/dizi" : 4,
        ]));
        set("coor/x", -3080);
        set("coor/y", -22110);
        set("coor/z", 0);
        setup();
        "/clone/board/xiake_b"->foo();
}

void init()
{
        add_action("do_push","push");
}

int do_push(string arg)
{
        object *inv,me=this_player();
        int n, i;
        n=query("neili", me);
        inv = all_inventory(me);
        for(i=sizeof(inv)-1; i>=0; i--)
        {
                if( (query("id", inv[i]) == "pai1") && 
                    (query_temp("own", inv[i]) != query("id", me)) )
                    return notify_fail("���͵�����˵������λ" +
                      RANK_D->query_respect(me) + "���������͵��Ŀ��˰ɣ�\n");
                if( (query("id", inv[i]) == "pai2") && 
                    (query_temp("own", inv[i]) != query("id", me)) )
                    return notify_fail("���͵�����˵������λ" +
                      RANK_D->query_respect(me) + "���������͵��Ŀ��˰ɣ�\n");
        }
        if( !arg || arg!="pingfeng")
        {
                write("��Ҫ��ʲôѽ��\n");
                return 1;
        }
        message_vision("$N������ǰվ��������һ���������ֽ���ס���硣\n", me);
        if (n >=100)
        {
                message_vision("$N����һ�������͵�һ�ƣ�ֻ������֮��¶��һ������������\n", me);
                set("exits/south", __DIR__"yongdao3");
                set("neili", n-100, me);
                remove_call_out("close");
                call_out("close",5, this_object());
        }
        else
        {
                message_vision("$N����һ�������͵�һ�ƣ�����ȴ˿��û����\n", me);
                set("neili", 0, me);
        }
        return 1;
}
void close(object room)
{
        message("visoin", "�����Զ��ֺ����ˡ�\n", room);
        delete("exits/south", room);
}