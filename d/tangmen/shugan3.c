//shugan3.c                �Ĵ����š������¹���

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�������");
        set("long",
      "����������ɵ�������������ʦү���������������չ��ƶ���ҹ����\n" 
      "�䣬��������ˣ������������ž�ѧ����˺ܶ���ӳ�����������ҹ������\n" 
      ); 
        set("area", "tangmen");
        setup();
}

void init()
{
        add_action("do_climb","climb");
        add_action("do_climb","pa");
}

int do_climb(string arg)
{
        object ob, room;

        ob = this_player();

        if ( arg && arg=="up" )
        {
                message_vision(HIC "$N���ŷ�ï����֦һ����������ȥ��\n" NOR, ob);

                if ( (int)ob->query_skill("dodge", 1) < 51 && (int)ob->query_skill("finger", 1) < 51 )
                {
                        message_vision(HIR "$N����һ��������ûץ��������ˤ��������\n" NOR, ob);
                        addn("qi", -10, ob);
                        return 1;
                }

                ob->move(__DIR__"shuding");
                return 1;
        }
        else
                if ( arg && arg=="down" )
                {
                        message_vision(HIC "$N���ŷ�ï����֦С��������������ȥ��\n" NOR, ob);
                        ob->move(__DIR__"shugan2");
                        return 1;
                }
                else
                        return notify_fail("��Ҫ����������\n");
}