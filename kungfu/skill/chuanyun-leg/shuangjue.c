// shuangjue.c  ȭ��˫��

#include <ansi.h>
inherit F_SSERVER;
#define PNAME "��ȭ��˫����"
int perform(object me, object target)
{
        int i, j, z, y;
        int flag;
        string fskill,sskill,bskill,pfname,pskill,cskill,cskill1;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname) )
   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("��������ʹ�á�ȭ��˫������\n");
                
        fskill = "xuantian-wuji";
        bskill = "leg";
        cskill = "cuff";
        cskill1= "zhentian-cuff";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
                cskill = "force";
                cskill1= "shenyuan-gong";
        }
        if( !query_temp("murong/xingyi", me) )
        {
                if (me->query_skill_prepared("cuff") != "zhentian-cuff" ||
                        me->query_skill_prepared("leg") != "chuanyun-leg" ||
                        me->query_skill_mapped("cuff") != "zhentian-cuff" ||
                        me->query_skill_mapped("leg") != "chuanyun-leg")
                        return notify_fail("�������޷�ʹ��"PNAME"���й�����\n");
        }
        if( (int)me->query_skill(cskill1, 1) < 100 )
                return notify_fail("���"+to_chinese(cskill1)+"������죬�޷�ʩչ"PNAME"��\n");
        if( (int)me->query_skill(cskill, 1) < 100 )
                return notify_fail("���"+to_chinese(cskill)+"������죬�޷�ʩչ��"PNAME"��\n");
        if( (int)me->query_skill(bskill, 1) < 100 )
                return notify_fail("���"+to_chinese(bskill)+"������죬�޷�ʩչ��"PNAME"��\n");
        if( (int)me->query_skill(sskill, 1) < 100 )
                return notify_fail("���"+to_chinese(sskill)+"������죬�޷�ʩչ"PNAME"��\n");
        if ((int)me->query_skill(fskill, 1) < 100)
                return notify_fail("���"+to_chinese(fskill)+"��򲻹����޷�ʩչ��"PNAME"��\n");
        if( (int)me->query_dex() < 30 )
                return notify_fail("�������Ƿ�ѣ��޷�ʩչ��"PNAME"��\n");
        if( query("max_neili", me)<500 )
                return notify_fail("��������������޷�ʩչ��"PNAME"��\n");
        if( query("neili", me)<400 )
                return notify_fail("��������������޷�ʩչ��"PNAME"��\n");
        i = me->query_skill(cskill,1);
        j = me->query_skill(bskill,1);
        z = me->query_skill("force",1);
        y = (i+j+z)/20;
        message_combatd(RED"$N"RED"һ����Х��ȭ����ʩ��ʹ�����ؾ�ѧ��ȭ��˫����Ѹ�����׵ع���$n"RED"��\n"NOR,me, target);
        addn("neili", -400, me);
        addn_temp("apply/str", y, me);
        addn_temp("apply/attack", y, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
        addn_temp("apply/str", -y, me);
        addn_temp("apply/attack", -y, me);
        me->start_busy(2);
        return 1;
}

string name() {return replace_string(replace_string(PNAME,"��",""),"��","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"֮"+name()+WHT"��"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                ����������������

        ����Ҫ��
                �����޼���100��
                �����ȷ�100��
                ����ȭ��100��
                ����ȭ��100��
                ������100��
                ��������30
                ������Ϊ500
                ����400
HELP
        );
        return 1;
}