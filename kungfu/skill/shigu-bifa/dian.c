// riyue.c 断云鞭法[日月无光]

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

        if( (int)me->query_skill("shigu-bifa",1) < 100)
                return notify_fail("你的「石鼓打穴笔法」还没学到家，用不了「点穴」绝招。\n");

        if( (int)me->query_skill("wuzheng-xinfa",1) < 100)
                return notify_fail("你的「无争心法」不够纯熟，用不了「点穴」绝招。\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧。\n");

        msg = HIC "$N大笔虚点，自右上角至左下角弯曲而下，劲力充沛，$n上半身穴道皆笼罩其中。\n"NOR;

        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/300){
                msg += HIW"$p感到双手、胸口、腹部、三处穴道微微一痛，顿时全身麻木不能动弹。\n" NOR;
                target->start_busy( (int)me->query_skill("shigu-bifa") / 30 +4);
                me->start_busy(random(2));
                addn("neili", -200, me);
        } else {
                msg += HIR"可是$p看破了$P的企图，并没有上当。\n" NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}