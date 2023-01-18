
#if NETWORKING



#include 	<gl.h>
#include 	<device.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"udpbrdcst.h"
#include	<sys/times.h>
#include	"arena.h"

#define readnet(temp) (recvbroadcast(enet,temp,4*sizeof(struct thing),IGNOREOWNMSG))

#define sendout(data) (sendbroadcast(enet,data,4*sizeof(struct thing), &arenaaddr))
#define INUSE(temp)	(used[temp.id])
struct sockaddr_in arenaaddr, hostaddr;
int enet;
int used[MAXPLAYERS];

/*
 * initialize communications, assign an id # to global var id
 */
init_comm()
{
    enet = getbroadcast("sgi-arena", &arenaaddr);
    if (enet == -2)
    {
	udp_warning();
	exit(0);
    }
    if ((id = check_full()) == -1)
    {
	printf("sorry, game is full\n");
	exit(0);
    }
    else
    {
	player[id].type = PLAYER;
	player[id].id   = id;
    }
}

/*
 * check for full game, return valid id, -1 if game is full
 * potential problem if one program is not sending packets 
 * for some reason.  
 */
check_full()
{
    int i;
    struct thing temp[4];
    struct tms tbuf;
    long t;

    for (i = 0, t = times(&tbuf)+120;
	 (i < 5 * MAXPLAYERS) || times(&tbuf) < t;
	 i++)
	if (readnet(temp))
	{
	    INUSE(temp[0]) = 1;
	}

    for (i = 0; i < MAXPLAYERS; i++)
	if (!(used[i])) return(i);
    return(-1);
}

exit_comm()
{
}

/*
 * read data off of the net.
 * put any player packets in the player array.
 * insert missiles into linked list
 * check to see if missiles kill current player
 */
read_net()
{
    struct thing temp[4];
    int i, temp_id;

    /*
     * read & process all available data off our port 
     * processing includes drawing 
     */

    while(readnet(temp)) 
    {
	temp_id = temp[0].id;
	if (temp[0].type & DEATH)
	{
	    player[temp_id].type = NOTHING;
	    shots[temp_id][0].type = NOTHING;
	    shots[temp_id][1].type = NOTHING;
	    shots[temp_id][2].type = NOTHING;
	    INUSE(temp[0]) = 0;
	}
	else
	{
	    player[temp_id] = temp[0];
            printf("player %d is active\n", temp_id);
	    INUSE(temp[0]) = 1;
	    shots[temp_id][0] = temp[1];
	    shots[temp_id][1] = temp[2];
	    shots[temp_id][2] = temp[3];
	    for (i=1; i<=3; i++)
	        if (temp[i].type & DEATH)
		    shots[temp_id][i-1].type = NOTHING;
	        else
	        {
		    shots[temp_id][i-1] = temp[i];
		    if ((temp[i].type & DID_HIT) &&
		        ((temp[i].type & HIT_WHAT) >> WHAT_SHIFT) == id)
		        hit_by(temp[i].type & MISSILE);
	        }
	}
    }
}

/*
 * send out all of my data, including any missiles.
 */
send_my_stuff()
{
    struct thing temp[4];

    bcopy(&player[id], temp, sizeof(struct thing));
    temp[0].xpos = xpos;
    temp[0].ypos = ypos;
    temp[0].zpos = zpos;
    temp[0].yrot = wrot;
    bcopy(shot, &temp[1], 3 * sizeof(struct thing));
    sendout(temp);
}


/*
 * send out all of my data, including any missiles.
 */
send_death()
{
    struct thing temp[4];
    int i;

    temp[0].type = PLAYER | DEATH;
    temp[0].id   = id;
    for (i=0; i < 3; i++)
	shot[i].type |= DEATH | i;
    bcopy(shot, &temp[1], 3 * sizeof(struct thing));
    sendout(temp);
}


udp_warning()
{
    printf("\n");
    printf("To run arena over the network you must add the following line\n");
    printf("to your /etc/services file.\n");
    printf("\n");
    printf("sgi-arena		5131/udp		# arena demo\n");
    printf("\n");
    printf("WARNING some machines can not handle large numbers of udp\n");
    printf("broadcast packets.  If you have machines from other vendors\n");
    printf("on your network, running arena -n on your network may bring\n");
    printf("them to a halt.  VAXes are known to have this problem.\n");
}

#endif // NETWORKING
