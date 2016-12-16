#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·经外奇脉·印堂穴" NOR, ({ "tongren i2", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "经外奇脉");
        set("xuewei_name", "印堂穴");
        set("chongxue_xiaoguo", "JING:30");
        set("neili_cost", "8000");
        setup();
}

