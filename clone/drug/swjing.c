// Code of ShenZhou
// shouwu.c ���ھ�

#include <ansi.h>

inherit ITEM;

void init();

void create()
{
        set_name( GRN "���ھ�" NOR , ({"shouwu jing", "shouwu"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�óɾ��ĺ����ڣ����������˼������ˣ����ѳ����Σ��������ҩЧ��\n");
                set("value", 8000);
                set("no_sell", 1);
                set("medicine", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        set("jing",query("max_jing",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        
        message_vision(HIY "$N����һ�����ھ���ҩЧ����ͨ���θ���ֱ����֫������������������ʹҲȫ���о������ˡ�\n" NOR, me);

        destruct(this_object());
        return 1;
}