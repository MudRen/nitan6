// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "缠身决" NOR; }

int perform(object me, object target)
{
        int lvl;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能对战斗中的对手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手使用。\n");

        if( query_temp("gb_chanshen", target) )
                return notify_fail("对方已经被你使"+name()+"缠住了！\n");

        if (target->is_busy())
                return notify_fail("对方正在忙乱中，放心大胆攻击吧！\n");

        if ((int)me->query_skill("xiaoyaoyou", 1) < 150)
                return notify_fail("你的逍遥游不够娴熟，不能使出"+name()+"！\n");

        if ((int)me->query_skill("shexing-diaoshou", 1) < 150)
                return notify_fail("你的蛇行刁手不够娴熟，不能使出"+name()+"！\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("你的混天气功等级不够，不能使出"+name()+"！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力太弱，不能使出"+name()+"！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的内力太少了，不能使出"+name()+"！\n");

        /*
        if( !query_temp("gb_huixuan", me) )
                return notify_fail("你没有使出逍遥回旋步，无法使出缠身决！\n");
        */

        lvl = ((int)me->query_skill("xiaoyaoyou", 1) +
               (int)me->query_skill("shexing-diaoshou", 1)) / 2;

        message_combatd(HIB "\n突然间$N口中发出“嘶嘶”的声音，双手半曲，三指上竖成蛇状，\n"
                        "陪合着潇遥步法，突然欺近$n的身边，令$n大吃一惊。\n" NOR, me, target);

        addn("neili", -100+random(50), me);

        addn_temp("apply/defense", -lvl/3, target);
        addn_temp("apply/armor", -lvl/3, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");
        if( ap / 2 + random(ap) > dp )
        {
                message_combatd(HIB "但见$N的身形有如蛇蝎缠身一般，环在$n的身边，令$n不知所措，\n"
                                "只觉的仿拂有无形的绳索慢慢的束缚了$n。\n" NOR, me, target);

                target->start_busy(3 + random(lvl / 120));
        }

        set_temp("gb_chanshen", 1, target);
        me->start_call_out( (: call_other, __FILE__, "remove_effect", target, lvl / 3 :), lvl / 25);

        return 1;
}

void remove_effect(object target,int lvl)
{
        if (! target) return;

        addn_temp("apply/defense", lvl, target);
        addn_temp("apply/armor", lvl, target);
        delete_temp("gb_chanshen", target);
        if (target->is_fighting())
        {
                // target->start_busy(1 + random(1));
                message_combatd(HIG "$N使出浑身解数，算是挣脱了蛇形刁手的诡异怪招。\n" NOR, target);
        }
}
