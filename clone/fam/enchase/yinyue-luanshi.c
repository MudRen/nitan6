inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "���¡�����" NOR, ({"yinyue luanshi", "yinyue luanshi" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 50000);
                set("enchase/name", "���¡�����");
                set("enchase/point", 70);
                set("enchase/type", "all");
                set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

