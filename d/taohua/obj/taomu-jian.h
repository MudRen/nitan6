//Cracked by Kafei

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int exp1, exp2, gain, gain1, gain2, bonus;
        int int1, int2, age1, age2;
        float gain3;
        mapping fam1, fam2;
//        object where;
        
//        where = environment(me);
        fam1=query("family", me);
        fam2=query("family", victim);

/*        if (strsrch(file_name(where), "/d/taohua/") < 0)
                return; 
*/
        if (!fam1 || fam1["family_name"] != "�һ���")
                return 0;
        if (!fam2 || fam2["family_name"] != "�һ���")
                return 0;

/*        if (!userp(victim)) 
                return;
*/
/*if( query("owner") != query("id", me) )
                return;
*/
        exp1=query("combat_exp", me);
        exp2=query("combat_exp", victim);
        int1 = me->query_int();
        int2 = victim->query_int();
        age1=query("age", me);
        age2=query("age", victim);
        
        if (exp1 > exp2) gain1 = (int)(exp1/exp2);
                else gain1 = (int)(exp2/exp1);
        if (gain1 > 2) gain1 = 0;
        if (int1 > int2) gain2 = int1-int2;
                else gain2 = int2-int1;
        if (gain2 > 4) gain2 = 0;
        if (age1 > age2) gain3 = age1/age2;
                else gain3 = age2/age1;
        if (gain3 > 1.2) gain3 = 0.2;
        
        gain = (int)((gain1+gain2)*gain3);
        if (gain > 3) gain = 3;
        bonus = damage_bonus%(int)(gain*(int2+int1)/40+1);
        addn("combat_exp", bonus, me);
        if( query("potential", victim)<query("max_potential", victim) )
        addn("potential", bonus, victim);
        victim->reset_action();
        set_heart_beat(1);
        return;
}