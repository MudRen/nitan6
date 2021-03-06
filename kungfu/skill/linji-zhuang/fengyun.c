
// fengyun.c

#include <ansi.h>

int exert(object me, object target)
{
        int level = me->query_skill("linji-zhuang", 1);

        if (level < 120) return notify_fail("你的临济十二庄修为还不够。\n");

        if( query("max_neili", me)<5*level )
                return notify_fail("你的内力还不够强。\n");

        if( query("neili", me)<4*level )
                return notify_fail("你的真气不够。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return notify_fail("你已经受伤过重，只怕一运真气便有生命危险！\n");

        if( query_temp("linji/fengyun", me) )
                return notify_fail("你此时四肢百骸真气鼓荡，不必再次运功。\n");

        set_temp("linji/fengyun", 1, me);
        write( HIY "你暗运风云两庄，心思浮云飘空之悠闲缓慢，默想狂风荡地之迅速紧急，\n一股丹田热气分注四肢百骸，但觉身手敏捷了许多。\n" NOR);
        message("vision",
                HIY + "只见" + me->name() + "微闭双眼，身旁凝起一圈白雾，瞬息间一股旋风卷过，"+me->name()+"身形又复清晰。\n" NOR,
                environment(me), me);

        addn("neili", -level, me);
        level /= 10;
        addn_temp("apply/dex", level, me);
        addn_temp("apply/attack", -level/2, me);
        addn_temp("apply/armor", level*15, me);
        addn_temp("apply/defense", level*5, me);

        me->start_call_out( (: call_other, __FILE__, "recover", me, level :), level * 10);

        return 1;
}

void recover(object me, int level)
{
        addn_temp("apply/dex", -level, me);
        addn_temp("apply/attack", level/2, me);
        addn_temp("apply/armor", -level*15, me);
        addn_temp("apply/defense", -level*5, me);
        delete_temp("linji/fengyun", me);

        tell_object(me, HIG"你风云行功已久，略觉步履沉重了一些。\n"NOR);
}