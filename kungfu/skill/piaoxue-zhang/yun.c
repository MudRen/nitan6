#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "云海明灯" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在战斗中对对手使用。\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("你必须空手才能施展" + name() + "。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的内功的修为不够，无法施展" + name() + "。\n");

        if (me->query_skill("piaoxue-zhang", 1) < 150)
                return notify_fail("你的飘雪穿云掌修为不够，无法施展" + name() + "。\n");

        if( query("neili", me)<200 || query("max_neili", me)<2000 )
                return notify_fail("你的真气不够，无法施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "piaoxue-zhang")
                return notify_fail("你没有激发飘雪穿云掌，无法施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("你没有准备使用飘雪穿云掌，无法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "一声暴喝，陡然施出飘雪穿云掌绝技「云海明灯」，瞬"
              "间连续攻出数招。\n" NOR;
        message_combatd(msg, me);

        addn("neili", -100, me);

        // 第一招
        addn_temp("apply/attack", 300, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // 第二招
        addn_temp("apply/attack", 600, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // 第三招
        addn_temp("apply/attack", 900, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // 消除攻击修正
        addn_temp("apply/attack", -1800, me);

        me->start_busy(1 + random(3));

        return 1;
}
