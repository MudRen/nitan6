// jiuzhuan.c ��ת��

#include <ansi.h>
#include "gift.h"

void create()
{
        set_name(HIY "��ת��" NOR, ({ "jiuzhuan jindan", "dan" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ�Ž�ɫ���ɵ�����˵��̫���Ͼ�"
                              "�����������鵤��ҩ���ɹ�����100%"
                            "����������ĵ�\n");
                set("base_value", 150000);
                set("base_weight", 200);
                set("base_unit", "��");
                set("only_do_effect", 1);
        }       
        setup();
}

int do_effect(object me)
{
        int effect;

        /*
        log_file("static/using", sprintf("%s(%s) eat ��ת�� at %s.\n",
                 me->name(1),query("id", me),ctime(time())));
        */

        effect = 0;
        message_vision("$Nһ������������һ��" + this_object()->name() +
                       "��\n", me);
        if( query("gift/int/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIM "������Լ���ͷ�Ը������ˡ�\n" NOR);
                addn("gift/xiandan", 1, me);
                addn("gift/int/succeed", 1, me);
                addn("int", 1, me);
        }

        if( query("gift/dex/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIR "������Լ����ȽŸ�����ˡ�\n" NOR);
                addn("gift/unknowdan", 1, me);
                addn("dex", 1, me);
                addn("gift/dex/succeed", 1, me);
        }

        if( query("gift/con/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIC "������Լ�����Ϣ��ͨ���ˡ�\n" NOR);
                addn("gift/xisuidan", 1, me);
                addn("con", 1, me);
                addn("gift/con/succeed", 1, me);
        }

        if( query("gift/str/succeed", me)<4 && random(2) )
        {
                effect++;
                write(HIG "������Լ���������ǿ���ˡ�\n" NOR);
                addn("gift/shenliwan", 1, me);
                addn("str", 1, me);
                addn("gift/str/succeed", 1, me);
        }

        write(HIM "ڤڤ������������ֻ������̨һƬ�����������ޱȡ�\n" NOR);
        addn("magic_points", 1000+random(1000), me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}