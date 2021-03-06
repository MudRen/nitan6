// shizi-zhan.c
// 十字战

inherit SKILL;

mapping *action = ({
([	"action"    :"$N坐马拉弓，击出一拳，正是一招「混元手」..",
    "lian"      :"$N坐马拉弓，击出一拳「混元手」，却总觉得有些不得要领",
    "jibie"     :8,
    "zhaoshi":"「混元手」",
    "sen"       :1,
	"dodge"     :0,
    "parry"     :0,
    "damage"     :10,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N双掌一错，使出「虚式冲天炮」，对准$n的$l连续拍出三掌",
    "lian"      :"$N双掌一错，使出「虚式冲天炮」，连续拍出三掌，结果左手把右手打得生疼",
    "jibie"     :16,      
    "zhaoshi":"「虚式冲天炮」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N吐气扬声，一招「狮子大张口」双手奔$n的头颈抢去",
    "lian"      :"$N一招「狮子大张口」，双手向假象中的敌人的头颈抢去",
    "jibie"     :24,
    "zhaoshi":"「狮子大张口」",
    "limb":"头颈",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N一招「擂拳寸腿」,起手向$n$l拍去...",
    "lian"      :"$N一招「擂拳寸腿」，起手向前拍去...",
    "jibie"     :32,    
    "zhaoshi":"「擂拳寸腿」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :10,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N左掌一翻，右掌推出，一个「劈锤」击向$n$l",
    "lian"      :"$N右掌慢慢推出，左掌一翻，配合右掌的变化",
    "jibie"     :40,
    "zhaoshi":"「劈锤」",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :25,
	"damage_type":	"瘀伤"
]),
([	"action"    :"$N使出一招「插腿」，脚踩七星步，一拳向$n$l击去",
    "lian"      :"$N慢慢使出一招「插腿」，仔细揣摩每一个变化",
    "jibie"     :48,
    "zhaoshi":"「插腿」",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"瘀伤"
]),
});

string * parry_msg = ({
    "$n一招「拖步冲锤」，双掌翻舞，$N眼前一花，失去了$n的踪影。\n",
    "$n两手握拳，一招「混元手」，格开了$N的一击。\n",
    "但见$n一招「擂拳寸腿」，跟上一步，化开了$N的攻势。\n",
});
    
int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    {    
        write("练拳必须空手。\n");
        return 0;
    }
    return 1;
}

int valid_lian( object me )
{   
    return valid_learn(me);
}

mapping query_action(int jibie)
{
	int i, size;

	size = sizeof( action );
	for ( i = 0; i < sizeof( action ); i++ )
		if ( action[ i ][ "jibie" ] > jibie )
		{
			size = i;
			break;
		}
    return action[ random( size ) ];
}

string query_zhaoshi( int jibie )
{
    int i;
    for ( i = 0; i < sizeof(action); i++ )
    {
        if ( action[ i ][ "jibie" ] >= jibie )
            return action[ i ][ "zhaoshi" ];
    }
    return "";
}

string query_xiuwei_type() { return "unarmed"; }

int query_dengji() { return 2; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }
