inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW "ѩ����" NOR, ({"snow ghost" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 500000);
                set("enchase/name", "ѩ����");
                set("enchase/point", 120);
                set("enchase/type", "wrists");
                                set("enchase/cur_firm", 90);
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

