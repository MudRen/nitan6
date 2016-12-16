#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIC "������" NOR, ({ "yangjing dan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "��");
                set("base_value", 50);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(A, me)")<10 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["jing"] == my["max_jing"])
        {
                write("�����ھ���״̬�ܺã��������" + name() + "��\n");
                return 1;
        }

//        me->set_temp("last_eat/dan(A)", time());

        message_vision(HIC "$N����һ�����������е���̨��һƬ�徻��\n" NOR, me);
        me->receive_curing("jing", 50);
        me->receive_heal("jing", 50);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}