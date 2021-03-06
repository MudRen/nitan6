// This program is a part of NT MudLIB
// stats cmds

#include <ansi.h>
#include <mudlib.h>
#include <command.h>

inherit F_CLEAN_UP;

int jingmai_effect(object ob, string str)
{
        if( query("jingmai/finish", ob) )
                return ZHOUTIAN_D->query_jingmai_effect(str);
        else
                return query("jingmai/" + str, ob);
}               

int main(object me, string arg)
{
        object ob;
        string sp;

        seteuid(getuid(me));

        if( !wizardp(me) && time()-query_temp("last_stats", me)<5 )
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");

        set_temp("last_stats", time(), me);
        MYGIFT_D->check_mygift(me, "newbie_mygift/istat");
        if (arg && arg != "")
        {
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("你要察看谁的状态？\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");
        } else
                ob = me;

        sp = HIM + (ob == me ? "你" : ob->name(1)) + "目前的各附加属性效果一览\n" NOR;
        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;

        sp += sprintf(HIC "【臂力附加】" HIG " %9d / %-9d"
                      HIC "【悟性附加】" HIG " %9d / %d\n"
                      HIC "【根骨附加】" HIG " %9d / %-9d"
                      HIC "【身法附加】" HIG " %9d / %d\n",
                      jingmai_effect(ob, "str")+query_temp("apply/attribute", ob)+query_temp("apply/str", ob),1000,
                      jingmai_effect(ob, "int")+query_temp("apply/attribute", ob)+query_temp("apply/int", ob),1000,
                      jingmai_effect(ob, "con")+query_temp("apply/attribute", ob)+query_temp("apply/con", ob),1000,
                      jingmai_effect(ob, "dex")+query_temp("apply/attribute", ob)+query_temp("apply/dex", ob),1000);

        sp += sprintf(HIC "【潜能上限】" HIM " %9d / %-9d"
                      HIC "【体会上限】" HIM " %9d / %d\n"
                      HIC "【内力上限】" HIM " %9d / %-9d"
                      HIC "【精力上限】" HIM " %9d / %d\n"
                      HIC "【气血上限】" HIM " %9d / %-9d"
                      HIC "【精气上限】" HIM " %9d / %d\n",
                      jingmai_effect(ob, "pot")+query_temp("apply/max_potential", ob),10000000,
                      jingmai_effect(ob, "mar")+query_temp("apply/max_experience", ob),10000000,
                      jingmai_effect(ob, "neili")+query_temp("apply/max_neili", ob),1000000,
                      jingmai_effect(ob, "jingli")+query_temp("apply/max_jingli", ob),5000000,
                      jingmai_effect(ob, "qi")+query_temp("apply/max_qi", ob),1000000,
                      jingmai_effect(ob, "jing")+query_temp("apply/max_jing", ob),500000);

        sp += sprintf(HIC "【研究次数】" HIY " %9d / %-9d"
                      HIC "【研究效果】" HIY " %9s / %s\n"
                      HIC "【练习次数】" HIY " %9d / %-9d"
                      HIC "【练习效果】" HIY " %9s / %s\n"
                      HIC "【学习次数】" HIY " %9d / %-9d"
                      HIC "【学习效果】" HIY " %9s / %s\n"
                      HIC "【汲取消耗】" HIY " %9d / %-9d"
                      HIC "【汲取效果】" HIY " %9s / %s\n",
                      jingmai_effect(ob, "research_times")+query_temp("apply/research_times", ob),3000,
                      jingmai_effect(ob, "research_effect")+query_temp("apply/research_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "practice_times")+query_temp("apply/practice_times", ob),3000,
                      jingmai_effect(ob, "practice_effect")+query_temp("apply/practice_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "learn_times")+query_temp("apply/learn_times", ob),3000,
                      jingmai_effect(ob, "learn_effect")+query_temp("apply/learn_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "derive_times")+query_temp("apply/derive_times", ob),3000,
                      jingmai_effect(ob, "derive_effect")+query_temp("apply/derive_effect", ob)+"%","1500%");

        sp += sprintf(WHT "【攻击等级】" HIW " %9d / %-9d"
                      WHT "【防御等级】" HIW " %9d / %d\n"
                      WHT "【躲闪等级】" HIW " %9d / %-9d"
                      WHT "【招架等级】" HIW " %9d / %d\n"
                      WHT "【绝招命中】" HIW " %9s / %-9s"
                      WHT "【绝招防御】" HIW " %9s / %s\n"
                      WHT "【兵器伤害】" HIG " %9d / %-9d"
                      WHT "【空手伤害】" HIG " %9d / %d\n"
                      WHT "【绝招伤害】" HIG " %9s / %-9s"
                      WHT "【战斗保护】" HIG " %9d / %d\n"
                      WHT "【附加伤害】" HIG " %9d / %-9d"
                      WHT "【附加保护】" HIG " %9d / %d\n"
                      /*
                      WHT "【改造伤害】" HIG " %9d / %-9d"
                      WHT "【改造保护】" HIG " %9d / %d\n"
                      */
                      WHT "【无视招架】" HIY " %9s / %-9s"
                      WHT "【无视躲闪】" HIY " %9s / %s\n"
                      WHT "【无视攻击】" HIY " %9s / %-9s"
                      WHT "【无视内功】" HIY " %9s / %s\n",
                      jingmai_effect(ob, "attack")+query_temp("apply/attack", ob),3000,
                      jingmai_effect(ob, "defense")+query_temp("apply/defense", ob),3000,
                      query_temp("apply/dodge", ob),3000,query_temp("apply/parry", ob),3000,
                      query_temp("apply/ap_power", ob)+"%","200%",query_temp("apply/dp_power", ob)+"%","200%",
                      jingmai_effect(ob, "damage")+query_temp("apply/damage", ob),200000,
                      jingmai_effect(ob, "damage")+query_temp("apply/unarmed_damage", ob),200000,
                      jingmai_effect(ob, "da_damage")+query_temp("apply/da_power", ob)+"%","200%",
                      jingmai_effect(ob, "armor")+query_temp("apply/armor", ob),200000,
                      query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                      query_temp("apply/avoid_parry", ob)+"%","90%",query_temp("apply/avoid_dodge", ob)+"%","90%",
                      query_temp("apply/avoid_attack", ob)+"%","90%",query_temp("apply/avoid_force", ob)+"%","90%");

        sp += sprintf(RED "【毒 伤 害】" RED " %9s / %-9s"
                      RED "【抗    毒】" RED " %9s / %s\n"
                      RED "【金 伤 害】" RED " %9s / %-9s"
                      RED "【抗    金】" RED " %9s / %s\n"
                      RED "【木 伤 害】" RED " %9s / %-9s"
                      RED "【抗    木】" RED " %9s / %s\n"
                      RED "【水 伤 害】" RED " %9s / %-9s"
                      RED "【抗    水】" RED " %9s / %s\n"
                      RED "【火 伤 害】" RED " %9s / %-9s"
                      RED "【抗    火】" RED " %9s / %s\n"
                      RED "【土 伤 害】" RED " %9s / %-9s"
                      RED "【抗    土】" RED " %9s / %s\n",
                      query_temp("apply/add_poison", ob)+"%","90%",query_temp("apply/reduce_poison", ob)+"%","90%",
                      query_temp("apply/add_metal", ob)+"%","90%",query_temp("apply/avoid_metal", ob)+"%","90%",
                      query_temp("apply/add_wood", ob)+"%","90%",query_temp("apply/avoid_wood", ob)+"%","90%",
                      query_temp("apply/add_water", ob)+"%","90%",query_temp("apply/avoid_water", ob)+"%","90%",
                      query_temp("apply/add_fire", ob)+"%","90%",query_temp("apply/avoid_fire", ob)+"%","90%",
                      query_temp("apply/add_earth", ob)+"%","90%",query_temp("apply/avoid_earth", ob)+"%","90%");
                              
        sp += sprintf(HIB "【内力恢复】" HIB " %9d / %-9d"
                      HIB "【生命恢复】" HIB " %9d / %d\n"
                      HIB "【精气恢复】" HIB " %9d / %-9d"
                      HIB "【伤转内力】" HIB " %9s / %s\n"
                      HIB "【偷取内力】" HIB " %9s / %-9s"
                      HIB "【偷取生命】" HIB " %9s / %s\n"
                      HIB "【额外奖励】" HIB " %9s / %-9s"
                      HIB "【额外经验】" HIB " %9s / %s\n"
                      HIB "【额外潜能】" HIB " %9s / %-9s"
                      HIB "【额外体会】" HIB " %9s / %s\n"
                      HIB "【额外真气】" HIB " %9s / %-9s"
                      HIB "【忽视忙乱】" HIB " %9s / %s\n",
                      query_temp("apply/ref_neili", ob),500,query_temp("apply/ref_qi", ob),200,
                      query_temp("apply/ref_jing", ob),200,query_temp("apply/qi_vs_neili", ob)+"%","90%",
                      query_temp("apply/suck_neili", ob)+"%","90%",query_temp("apply/suck_qi", ob)+"%","90%",
                      query_temp("apply/add_reward", ob)+"%","120%",query_temp("apply/add_exp", ob)+"%","210%",
                      query_temp("apply/add_pot", ob)+"%","210%",query_temp("apply/add_mar", ob)+"%","210%",
                      query_temp("apply/add_force", ob)+"%","210%",query_temp("apply/avoid_busy", ob)+"%","90%");
                      
        sp += sprintf(WHT "【寻 金 率】" HIM " %9s / %-9s"
                      WHT "【寻 宝 率】" HIM " %9s / %s\n"
                      WHT "【杀    戮】" CYN " %9s / %-9s"
                      WHT "【破    气】" CYN " %9s / %s\n"
                      WHT "【双倍伤害】" CYN " %9s / %-9s"
                      WHT "【破    甲】" CYN " %9s / %s\n"
                      WHT "【致    盲】" CYN " %9s / %-9s"
                      WHT "【忽视致盲】" CYN " %9s / %s\n"
                      WHT "【天魔附体】" CYN " %9s / %-9s"
                      WHT "【战神附体】" CYN " %9s / %s\n",
                      query_temp("apply/gold_find", ob)+"%","100%",
                      jingmai_effect(ob, "magic_find")+query_temp("apply/magic_find", ob)+"%","300%",
                      query_temp("apply/slaughter", ob)+"%","90%",query_temp("apply/clear_force", ob)+"%","90%",
                      query_temp("apply/double_damage", ob)+"%","200%",query_temp("apply/through_armor", ob)+"%","90%",
                      query_temp("apply/add_blind", ob)+"%","90%",query_temp("apply/avoid_blind", ob)+"%","90%",
                      query_temp("apply/absorb_blood", ob)+"%","90%",query_temp("apply/full_self", ob)+"%","90%");
                      

        sp += sprintf(HIY "【冰    冻】" HIM " %9s / %-9s"
                      HIY "【忽视冰冻】" HIM " %9s / %s\n"
                      HIY "【眩    晕】" HIM " %9s / %-9s"
                      HIY "【忽视眩晕】" HIM " %9s / %s\n"
                      HIY "【遗    忘】" HIM " %9s / %-9s"
                      HIY "【忽视遗忘】" HIM " %9s / %s\n"
                      HIY "【忙    乱】" HIM " %9d / %-9d"
                      HIY "【化解忙乱】" HIM " %9d / %d\n"
                      HIY "【虚    弱】" HIM " %9s / %-9s"
                      HIY "【忽视虚弱】" HIM " %9s / %s\n"
                      HIY "【追加伤害】" HIM " %9s / %-9s"
                      HIY "【化解伤害】" HIM " %9s / %s\n"
                      HIY "【伤害反噬】" HIM " %9s / %-9s"
                      HIY "【浴血重生】" HIM " %9s / %s\n"                      
                      HIY "【必 杀 率】" HIM " %9s / %-9s"
                      HIY "【提升技能】" HIM " %9d / %d\n",
                      query_temp("apply/add_freeze", ob)+"%","90%",query_temp("apply/avoid_freeze", ob)+"%","90%",
                      query_temp("apply/add_dizziness", ob)+"%","90%",query_temp("apply/avoid_dizziness", ob)+"%","90%",                    
                      query_temp("apply/add_forget", ob)+"%","90%",query_temp("apply/avoid_forget", ob)+"%","90%",
                      query_temp("apply/add_busy", ob),90,query_temp("apply/reduce_busy", ob),90,
                      query_temp("apply/add_weak", ob)+"%","90%",query_temp("apply/avoid_weak", ob)+"%","90%",
                      query_temp("apply/add_damage", ob)+"%","200%",
                      jingmai_effect(ob, "reduce_damage")+query_temp("apply/reduce_damage", ob)+"%","90%",
                      query_temp("apply/counter_damage", ob)+"%","90%",query_temp("apply/avoid_die", ob)+"%","90%",
                      query_temp("apply/fatal_blow", ob)+"%","90%",query_temp("apply/add_skill", ob),3000);

        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;

        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR,
                        LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

        /*
        if (MEMBER_D->is_valid_member(ob))
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR);
        else
        */
        {
                if( query("online_time", ob)/3<query("offline_time", ob) )
                        set("offline_time",query("online_time",  ob)/3, ob);
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR,
                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
        }

        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                      time_period(query("time_reward/quest", ob)));
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                      time_period(query("time_reward/study", ob)));


        me->start_more(sp);
        return 1;
}
