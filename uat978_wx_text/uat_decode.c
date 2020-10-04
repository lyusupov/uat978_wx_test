// Part of dump978, a UAT decoder.
//
// Copyright 2015, Oliver Jowett <oliver@mutability.co.uk>
//

#ifndef NULL
#define NULL   ((void *) 0)
#endif

#include <math.h>
#include <string.h>
#include <assert.h>

#include <time.h>

#include "uat.h"
#include "uat_decode.h"

#include "metar.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static char gs_ret[80];

static void get_gs_name(char *Word,int len);

static void get_gs_name(char *Word,int len){

	char temp_stn[5]=" ";

	strncpy(temp_stn,Word,4);
	strcpy(gs_ret,"not found      ");

	for(int i=0; i < len; i++){

		if(*gs_list[i].gs_call == '\0')
	  	         return;
	  	if(strcmp(gs_list[i].gs_call, temp_stn)==0){
	  		strncpy(gs_ret,gs_list[i].gs_loc,75);
 	  	    	 return;
	  	}
	 }
     return;
}
static void get_sua_text(char *Word, FILE *to);
static void get_sua_text(char *Word, FILE *to){

	char *token;
	char sua_sch_id[10];
	char sua_aspc_id[7];
	char sua_sch_stat[2];
	char sua_aspc_ty[2];
	char sua_aspc_nm[50];

	char sua_st_tm[11];char sua_st_yy[3];char sua_st_mm[3];char sua_st_dd[3];
	char sua_st_hh[3]; char sua_st_mn[3];

	char sua_en_tm[11];char sua_en_yy[3];char sua_en_mm[3];char sua_en_dd[3];
	char sua_en_hh[3]; char sua_en_mn[3];

	char sua_low_alt[10];
	char sua_hg_alt[10];
	char sua_sep_rl[2];
	char sua_shp_ind[2];
	char sua_nfdc_id[10];
	char sua_nfcd_nm[50];
	char sua_dafif_id[10];
	char sua_dafif_nm[50];

	token = strsep(&Word,"|");
	strcpy(sua_sch_id,token);
	fprintf(filesua," Schedule ID    : %s ",sua_sch_id);
	token = strsep(&Word,"|");
	strcpy(sua_aspc_id,token);
	fprintf(filesua," Airspace ID: %s\n",sua_aspc_id);
	token = strsep(&Word,"|");
	strcpy(sua_sch_stat,token);
	if (strcmp(sua_sch_stat,"W") ==0){
		fprintf(filesua," Schedule Status: %s Waiting to Start\n",sua_sch_stat);}
	else if (strcmp(sua_sch_stat,"P")==0){
		fprintf(filesua," Schedule Status: %s Pending Approval\n",sua_sch_stat);}
	else if (strcmp(sua_sch_stat,"H")==0){
			fprintf(filesua," Schedule Status: %s Activated for Use\n",sua_sch_stat);}

	token = strsep(&Word,"|");
	strcpy(sua_aspc_ty,token);
	if (strcmp(sua_aspc_ty,"W") ==0){
		fprintf(filesua," Airspace Type  : %s Warning Area\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"R") ==0){
		fprintf(filesua," Airspace Type  : %s Restricted Area\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"M") ==0){
		fprintf(filesua," Airspace Type  : %s Military Operations Area\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"P") ==0){
		fprintf(filesua," Airspace Type  : %s Prohibited Area\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"L") ==0){
		fprintf(filesua," Airspace Type  : %s Alert Area\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"A") ==0){
		fprintf(filesua," Airspace Type  : %s ATCAA\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"I") ==0){
		fprintf(filesua," Airspace Type  : %s Instrument Route\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"V") ==0){
		fprintf(filesua," Airspace Type  : %s Visual Route\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"S") ==0){
		fprintf(filesua," Airspace Type  : %s Slow Route\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"B") ==0){
		fprintf(filesua," Airspace Type  : %s Military Route (Refueling)\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"O") ==0){
		fprintf(filesua," Airspace Type  : %s Other\n",sua_aspc_ty);}
	else if (strcmp(sua_aspc_ty,"T") ==0){
		fprintf(filesua," Airspace Type  : %s Refueling Track\n",sua_aspc_ty);}

	token = strsep(&Word,"|");
	strcpy(sua_aspc_nm,token);
	fprintf(filesua," Airspace Name  : %s\n",sua_aspc_nm);
	token = strsep(&Word,"|");

	strcpy(sua_st_tm,token);
	 snprintf(sua_st_yy, 3,"%s",sua_st_tm);
	 snprintf(sua_st_mm, 3,"%s",sua_st_tm+2);
	 snprintf(sua_st_dd, 3,"%s",sua_st_tm+4);
	 snprintf(sua_st_hh, 3,"%s",sua_st_tm+6);
	 snprintf(sua_st_mn, 3,"%s",sua_st_tm+8);

	fprintf(filesua," Start Time     : %s/%s/20%s %s:%s",
			 sua_st_mm,sua_st_dd,sua_st_yy,sua_st_hh, sua_st_mn);

	token = strsep(&Word,"|");
	strcpy(sua_en_tm,token);
	 snprintf(sua_en_yy, 3,"%s",sua_en_tm);
	 snprintf(sua_en_mm, 3,"%s",sua_en_tm+2);
	 snprintf(sua_en_dd, 3,"%s",sua_en_tm+4);
	 snprintf(sua_en_hh, 3,"%s",sua_en_tm+6);
	 snprintf(sua_en_mn, 3,"%s",sua_en_tm+8);

	fprintf(filesua," End Time: %s/%s/20%s %s:%s\n",
			 sua_en_mm,sua_en_dd,sua_en_yy,sua_en_hh,sua_en_mn);

	token = strsep(&Word,"|");
	strcpy(sua_low_alt,token);
	fprintf(filesua," Low Altitude   : %s ",sua_low_alt);

	token = strsep(&Word,"|");
	strcpy(sua_hg_alt,token);
	fprintf(filesua," High Altitude: %s\n",sua_hg_alt);

	token = strsep(&Word,"|");
	strcpy(sua_sep_rl,token);
	if (strcmp(sua_sep_rl,"A") ==0){
		fprintf(filesua," Separation Rule: %s Aircraft Rule ",sua_sep_rl);}
	else if (strcmp(sua_sep_rl,"O") ==0){
		fprintf(filesua," Separation Rule: %s Other Rule ",sua_sep_rl);}
	else {
		fprintf(filesua," Separation Rule:    Unspecified ");
	}
	token = strsep(&Word,"|");
	if (token){
		strcpy(sua_shp_ind,token);     //13
		if (strcmp(sua_shp_ind,"N") ==0){
			fprintf(filesua," Shape Indicator: %s No Shape Defined\n",sua_shp_ind);}
		else if	(strcmp(sua_shp_ind,"Y") ==0){
			fprintf(filesua," Shape Indicator: %s Has Shape Defined\n",sua_shp_ind);}
	}
	token = strsep(&Word,"|");
	if (token){
		strcpy(sua_nfdc_id,token);      //14
		fprintf(filesua," NFDC ID        : %s",sua_nfdc_id);
	}
	token = strsep(&Word,"|");
	if (token) {
		strcpy(sua_nfcd_nm,token);      //15
		fprintf(filesua,"      NFCD Name: %s\n",sua_nfcd_nm);
	}
	token = strsep(&Word,"|");
	if (token) {
		strcpy(sua_dafif_id,token);       //16
		fprintf(filesua," DAFIF ID       : %s",sua_dafif_id);
	}
	token = strsep(&Word,"|");
	if (token) {
		strcpy(sua_dafif_nm,token);      //17
		fprintf(filesua,"      DAFIF Name: %s\n",sua_dafif_nm);
	}

	fflush(filesua);

}

static void get_pirep(char *Word, FILE *to);

static void get_pirep(char *Word, FILE *to){

    char *token;
    char pirep_stn[5];
    char pirep_OV[20];		// Location
    char pirep_TM[10]; char pirep_hr[5]; char pirep_mn[3];		// DateTime
    char pirep_FL[5];		// Flight Level
    char pirep_TP[6];		// a/c type
    char pirep_SK[50];		// Cloud
    char pirep_WX[20];		// Weather
    char pirep_TA[5];		// Temperature
    char pirep_WV[10];		// Wind Speed Direction
    char pirep_TB[30];  	// Turbulence
    char pirep_IC[20];		// Icing
    char pirep_RM[100]; 	// Remarks

	token = strtok(Word," ");
	strcpy(pirep_stn,"K");
	strcat(pirep_stn,token);

    get_gs_name(pirep_stn,reccount);

    fprintf(to,"PIREP REPORT:\n");
    fprintf(filepirep,"PIREP REPORT:\n");
 	time_t current_time = time(NULL);
 	char * tm=ctime(&current_time);
    tm[strlen(tm)-1] = '\0';
	fprintf(to," Time           : %s\n", tm);
	fprintf(filepirep," Time           : %s\n", tm);
    fprintf(to," Station        : %s - %s\n",pirep_stn, gs_ret);
    fprintf(filepirep," Station        : %s - %s\n",pirep_stn, gs_ret);

    token = strtok(0," ");

    if( strcmp(token,"UUA") == 0 ){
    	fprintf(to," URGENT REPORT\n");
    	fprintf(filepirep," URGENT REPORT\n");
    }
        else if  ( strcmp(token,"UA") == 0 ){
        	fprintf(to," Routine Report\n");
        	fprintf(filepirep," Routine Report\n");
        }
    else {
    	fprintf(to," Unknown Report\n");
    	fprintf(filepirep," Unknown Report\n");
    }

    while ((token = strtok(0, "/"))) {

    	if (strncmp(token,"OV",2) == 0) {
    		strcpy(pirep_OV,token+3);
    		fprintf(to," Location       : %s\n",pirep_OV);
    		fprintf(filepirep," Location       : %s\n",pirep_OV);
    	 }
    	 else if (strncmp(token,"TM",2) == 0) {
    		 strcpy(pirep_TM,token);
    		 snprintf(pirep_hr, 3,"%s",pirep_TM+3);
    		 snprintf(pirep_mn, 3,"%s",pirep_TM+5);
    		 fprintf(to," Time           : %s:%sz\n",pirep_hr,pirep_mn);
    		 fprintf(filepirep," Time           : %s:%sz\n",pirep_hr,pirep_mn);
    	 }
    	 else if (strncmp(token,"FL",2) == 0) {
    		 strcpy(pirep_FL,token+2);
    	     fprintf(to," Flight Level   : %s\n",pirep_FL);
    	     fprintf(filepirep," Flight Level   : %s\n",pirep_FL);
    	 }
    	 else if (strncmp(token,"TP",2) == 0) {
    		 strcpy(pirep_TP,token+3);
    		 fprintf(to," A/C Type       : %s\n",pirep_TP);
    		 fprintf(filepirep," A/C Type       : %s\n",pirep_TP);
    	 }
    	 else if (strncmp(token,"SK",2) == 0) {
    		 strcpy(pirep_SK,token+3);
    	     fprintf(to," Cloud Layers   : %s\n",pirep_SK);
    	     fprintf(filepirep," Cloud Layers   : %s\n",pirep_SK);
    	 }
    	 else if (strncmp(token,"WX",2) == 0) {
 	     	 strcpy(pirep_WX,token+3);
    	     fprintf(to," Weather        : %s\n",pirep_WX);
    	     fprintf(filepirep," Weather        : %s\n",pirep_WX);
    	 }
       	 else if (strncmp(token,"TA",2) == 0) {
    	     strcpy(pirep_TA,token+3);
        	 fprintf(to," Temperature    : %s(c)\n",pirep_TA);
        	 fprintf(filepirep," Temperature    : %s(c)\n",pirep_TA);
       	 }
         else if (strncmp(token,"WV",2) == 0) {
        	 strcpy(pirep_WV,token+3);
             fprintf(to," WndSpdDir      : %s\n",pirep_WV);
             fprintf(filepirep," WndSpdDir      : %s\n",pirep_WV);
         }
         else if (strncmp(token,"TB",2) == 0) {
    		 strcpy(pirep_TB,token+3);
    	     fprintf(to," Turbulence     : %s\n",pirep_TB);
    	     fprintf(filepirep," Turbulence     : %s\n",pirep_TB);
         }
         else if (strncmp(token,"IC",2) == 0) {
    		 strcpy(pirep_IC,token+3);
    	     fprintf(to," Icing          : %s\n",pirep_IC);
    	     fprintf(filepirep," Icing          : %s\n",pirep_IC);
         }
    	 else if (strncmp(token,"RM",2) == 0) {
    		 strcpy(pirep_RM,token+3);
    		 token = strtok(0, "/");
    		 if (token){
    			 fprintf(to," Remarks        : %s",pirep_RM);
    			 fprintf(filepirep," Remarks        : %s",pirep_RM);
    			 fprintf(to,"/%s\n",token);
    			 fprintf(filepirep,"/%s\n",token);}
    		   	   else {
    		   		   fprintf(to," Remarks        : %s\n",pirep_RM);
    		   		   fprintf(filepirep," Remarks        : %s\n",pirep_RM);
    		   	   }
    	 }
    }
    fflush(filepirep);
}

static void uat_decode_hdr(uint8_t *frame, struct uat_adsb_mdb *mdb)
{
    mdb->mdb_type = (frame[0] >> 3) & 0x1f;
    mdb->address_qualifier = (address_qualifier_t) (frame[0] & 0x07);
    mdb->address = (frame[1] << 16) | (frame[2] << 8) | frame[3];
}

static const char *object_element_names[14] = {
		"Temporary Flight Restriction",
		"Parachute Jumping /Sky Diving",
		"Terminal Radar Service Area",
		"Airport Advisory Area",
		"VFR Flyway",
		"VFR Corridor",
		"VFR Transition Route",
		"Terminal Area VFR Route",
		"Prohibited Area ",
		"Restricted Area ",
		"Military Operations Area",
		"Warning Area",
		"Military Training Route",
		"Air Defense Identification Zone"
};

static const char *address_qualifier_names[8] = {
		"ICAO address via ADS-B",
		"reserved (national use)",
		"ICAO address via TIS-B",
		"TIS-B track file address",
		"Vehicle address",
		"Fixed ADS-B Beacon Address",
		"reserved (6)",
		"reserved (7)"
};

static void uat_display_hdr(const struct uat_adsb_mdb *mdb, FILE *to)
{
	fprintf(to,"HDR:");

	time_t current_time = time(NULL);
	struct tm *tm = localtime(&current_time);
	fprintf(to,"   Time: %s", asctime(tm));
	fprintf(to," ICAO:    %06X    (%s)\n",
			mdb->address,
			address_qualifier_names[mdb->address_qualifier]);
}

static double dimensions_widths[16] = {
    11.5, 23, 28.5, 34, 33, 38, 39.5, 45, 45, 52, 59.5, 67, 72.5, 80, 80, 90
};

static void uat_decode_sv(uint8_t *frame, struct uat_adsb_mdb *mdb)
{
    uint32_t raw_lat, raw_lon, raw_alt;

   	mdb->has_sv = 1;
    mdb->nic = (frame[11] & 15);

    raw_lat = (frame[4] << 15) | (frame[5] << 7) | (frame[6] >> 1);
    raw_lon = ((frame[6] & 0x01) << 23) | (frame[7] << 15) | (frame[8] << 7) | (frame[9] >> 1);
    
    if (mdb->nic != 0 || raw_lat != 0 || raw_lon != 0) {
        mdb->position_valid = 1;
        mdb->lat = raw_lat * 360.0 / 16777216.0;
        if (mdb->lat > 90)
            mdb->lat -= 180;
        mdb->lon = raw_lon * 360.0 / 16777216.0;
        if (mdb->lon > 180)
            mdb->lon -= 360;
    }

    raw_alt = (frame[10] << 4) | ((frame[11] & 0xf0) >> 4);
    if (raw_alt != 0) {
        mdb->altitude_type = (frame[9] & 1) ? ALT_GEO : ALT_BARO;
        mdb->altitude = (raw_alt - 1) * 25 - 1000;
    }
    
    mdb->airground_state = (frame[12] >> 6) & 0x03;

    switch (mdb->airground_state) {
    case AG_SUBSONIC:
    case AG_SUPERSONIC:
        {
        	int raw_ns, raw_ew, raw_vvel;
            
        	raw_ns = ((frame[12] & 0x1f) << 6) | ((frame[13] & 0xfc) >> 2);
            if ((raw_ns & 0x3ff) != 0) {
                mdb->ns_vel_valid = 1;
                mdb->ns_vel = ((raw_ns & 0x3ff) - 1);
                if (raw_ns & 0x400)
                    mdb->ns_vel = 0 - mdb->ns_vel;
                if (mdb->airground_state == AG_SUPERSONIC)
                    mdb->ns_vel *= 4;
            }
            
            raw_ew = ((frame[13] & 0x03) << 9) | (frame[14] << 1) | ((frame[15] & 0x80) >> 7);
            if ((raw_ew & 0x3ff) != 0) {
                mdb->ew_vel_valid = 1;
                mdb->ew_vel = ((raw_ew & 0x3ff) - 1);
                if (raw_ew & 0x400)
                    mdb->ew_vel = 0 - mdb->ew_vel;
                if (mdb->airground_state == AG_SUPERSONIC)
                    mdb->ew_vel *= 4;
            }
            
            if (mdb->ns_vel_valid && mdb->ew_vel_valid) {
                if (mdb->ns_vel != 0 || mdb->ew_vel != 0) {
                    mdb->track_type = TT_TRACK;
                    mdb->track = (uint16_t)(360 + 90 - atan2(mdb->ns_vel, mdb->ew_vel) * 180 / M_PI) % 360;
                }
                
                mdb->speed_valid = 1;
                mdb->speed = (int) sqrt(mdb->ns_vel * mdb->ns_vel + mdb->ew_vel * mdb->ew_vel);
            }

            raw_vvel = ((frame[15] & 0x7f) << 4) | ((frame[16] & 0xf0) >> 4);
            if ((raw_vvel & 0x1ff) != 0) {
                mdb->vert_rate_source = (raw_vvel & 0x400) ? ALT_BARO : ALT_GEO;
                mdb->vert_rate = ((raw_vvel & 0x1ff) - 1) * 64;
                if (raw_vvel & 0x200)
                    mdb->vert_rate = 0 - mdb->vert_rate;
            }                
        }
        break;

    case AG_GROUND:
        {
            int raw_gs, raw_track;

            raw_gs = ((frame[12] & 0x1f) << 6) | ((frame[13] & 0xfc) >> 2);
            if (raw_gs != 0) {
                mdb->speed_valid = 1;
                mdb->speed = ((raw_gs & 0x3ff) - 1);
            }

            raw_track = ((frame[13] & 0x03) << 9) | (frame[14] << 1) | ((frame[15] & 0x80) >> 7);
            switch ((raw_track & 0x0600)>>9) {
            case 1: mdb->track_type = TT_TRACK; break;
            case 2: mdb->track_type = TT_MAG_HEADING; break;
            case 3: mdb->track_type = TT_TRUE_HEADING; break;
            }

            if (mdb->track_type != TT_INVALID)
                mdb->track = (raw_track & 0x1ff) * 360 / 512;

            mdb->dimensions_valid = 1;
            mdb->length = 15 + 10 * ((frame[15] & 0x38) >> 3);
            mdb->width = dimensions_widths[(frame[15] & 0x78) >> 3];
            mdb->position_offset = (frame[15] & 0x04) ? 1 : 0;
        }
        break;

    case AG_RESERVED:
        // nothing
        break;
    }
    
    if ((frame[0] & 7) == 2 || (frame[0] & 7) == 3) {
        mdb->utc_coupled = 0;
        mdb->tisb_site_id = (frame[16] & 0x0f);
    } else {
        mdb->utc_coupled = (frame[16] & 0x08) ? 1 : 0;
        mdb->tisb_site_id = 0;
    }
}

static void uat_display_sv(const struct uat_adsb_mdb *mdb, FILE *to)
{
	if (!mdb->has_sv)
        return;

    if (mdb->position_valid)
        fprintf(to, " Lat:   %+.4f    Lon:  %+.4f",
        		mdb->lat,
                mdb->lon);

    switch (mdb->altitude_type) {
    case ALT_BARO:
        fprintf(to, "  Alt:  %d ft (barometric)",
                mdb->altitude);
        break;
    case ALT_GEO:
        fprintf(to, "  Alt:  %d ft (geometric)",
                mdb->altitude);
        break;
    default:
        break;
    }

    if (mdb->speed_valid)
        fprintf(to, "  Speed:  %u kt\n",
                mdb->speed);

    if (mdb->dimensions_valid)
        fprintf(to, " Size: %.1fm L x %.1fm W%s\n",
                mdb->length, mdb->width,
                mdb->position_offset ? " (position offset applied)" : "");
}

static char base40_alphabet[40] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ  ..";
static void uat_decode_ms(uint8_t *frame, struct uat_adsb_mdb *mdb)
{
    uint16_t v;
    int i;

    mdb->has_ms = 1;

    v = (frame[17]<<8) | (frame[18]);
    mdb->emitter_category = (v/1600) % 40;
    mdb->callsign[0] = base40_alphabet[(v/40) % 40];
    mdb->callsign[1] = base40_alphabet[v % 40];
    v = (frame[19]<<8) | (frame[20]);
    mdb->callsign[2] = base40_alphabet[(v/1600) % 40];
    mdb->callsign[3] = base40_alphabet[(v/40) % 40];
    mdb->callsign[4] = base40_alphabet[v % 40];
    v = (frame[21]<<8) | (frame[22]);
    mdb->callsign[5] = base40_alphabet[(v/1600) % 40];
    mdb->callsign[6] = base40_alphabet[(v/40) % 40];
    mdb->callsign[7] = base40_alphabet[v % 40];
    mdb->callsign[8] = 0;

    // trim trailing spaces
    for (i = 7; i >= 0; --i) {
        if (mdb->callsign[i] == ' ')
            mdb->callsign[i] = 0;
        else
            break;
    }

    mdb->emergency_status = (frame[23] >> 5) & 7;
    mdb->uat_version = (frame[23] >> 2) & 7;
    mdb->sil = (frame[23] & 3);
    mdb->transmit_mso = (frame[24] >> 2) & 0x3f;
    mdb->nac_p = (frame[25] >> 4) & 15;
    mdb->nac_v = (frame[25] >> 1) & 7;
    mdb->nic_baro = (frame[25] & 1);
    mdb->has_cdti = (frame[26] & 0x80 ? 1 : 0);
    mdb->has_acas = (frame[26] & 0x40 ? 1 : 0);
    mdb->acas_ra_active = (frame[26] & 0x20 ? 1 : 0);
    mdb->ident_active = (frame[26] & 0x10 ? 1 : 0);
    mdb->atc_services = (frame[26] & 0x08 ? 1 : 0);
    mdb->heading_type = (frame[26] & 0x04 ? HT_MAGNETIC : HT_TRUE);
    if (mdb->callsign[0])
        mdb->callsign_type = (frame[26] & 0x02 ? CS_CALLSIGN : CS_SQUAWK);
}

static const char *emitter_category_names[40] = {

		"No aircraft type information",
		"Light < 15 500 lbs",
		"Small – 15,500 to 75,000 lbs",
		"Large – 75,000 to 300,000 lbs",
		"High Vortex Large",
		"Heavy - > 300,000 lbs",
		"Highly Maneuverable",
		"Rotocraft",
		"Unassigned 8",
		"Glider/sailplane",
		"Lighter than air",
		"Parachutist/sky diver",
		"Ultra light/hang glider/paraglider",
		"Unassigned 13",
		"Unmanned aerial vehicle",
		"Space/trans-atmospheric vehicle",
		"Unassigned 16",
		"Surface vehicle—emergency vehicle",
		"Surface vehicle—service vehicle",
		"Point Obstacle (includes tethered balloons)",
		"Cluster Obstacle"
		"Line Obstacle",
        "reserved (22)",
		"reserved (23)",                           // C7
		"reserved (24)",
		"reserved (25)",
		"reserved (26)",
    	"reserved (27)",
    	"reserved (28)",
    	"reserved (29)",
    	"reserved (30)",
    	"reserved (31)",
    	"reserved (32)",
    	"reserved (33)",
    	"reserved (34)",
    	"reserved (35)",
    	"reserved (36)",
    	"reserved (37)",
    	"reserved (38)",
    	"reserved (39)"
};    

static const char *emergency_status_names[8] = {

		"No emergency",
		"**** General emergency ****",
		"**** Lifeguard / Medical emergency ****",
		"**** Minimum fuel ****",
		"**** No communications ****",
		"**** Unlawful interference ****",
		"**** Downed aircraft ****",
		"reserved"
};

static void uat_display_ms(const struct uat_adsb_mdb *mdb, FILE *to)
{
    if (!mdb->has_ms)
        return;

    fprintf(to,
    		" Reg:%2s%9s"
            "    Category: %s\n"
            " Emergency status:  %s\n",
            mdb->callsign_type == CS_SQUAWK ? "sq" : "",
            mdb->callsign_type == CS_INVALID ? "      n/a" : mdb->callsign,
            emitter_category_names[mdb->emitter_category],
            emergency_status_names[mdb->emergency_status]);
}

static void uat_decode_auxsv(uint8_t *frame, struct uat_adsb_mdb *mdb)
{
    int raw_alt = (frame[29] << 4) | ((frame[30] & 0xf0) >> 4);
    if (raw_alt != 0) {
        mdb->sec_altitude = (raw_alt - 1) * 25 - 1000;
        mdb->sec_altitude_type = (frame[9] & 1) ? ALT_BARO : ALT_GEO;
    } else {
        mdb->sec_altitude_type = ALT_INVALID;
    }

    mdb->has_auxsv = 1;
}    

static void uat_display_auxsv(const struct uat_adsb_mdb *mdb, FILE *to)
{
    if (!mdb->has_auxsv)
        return;
}

void uat_decode_adsb_mdb(uint8_t *frame, struct uat_adsb_mdb *mdb)
{
    static struct uat_adsb_mdb mdb_zero;

    *mdb = mdb_zero;

    uat_decode_hdr(frame, mdb);   

    switch (mdb->mdb_type) {
    case 0: 	// HDR SV
    case 4: 	// HDR SV (TC+0) (TS)
    case 7: 	// HDR SV reserved
    case 8: 	// HDR SV reserved
    case 9: 	// HDR SV reserved
    case 10: 	// HDR SV reserved
        uat_decode_sv(frame, mdb);
        break;

    case 1: 	// HDR SV MS AUXSV
        uat_decode_sv(frame, mdb);
        uat_decode_ms(frame, mdb);
        uat_decode_auxsv(frame, mdb);
        break;

    case 2: 	// HDR SV AUXSV
    case 5: 	// HDR SV (TC+1) AUXSV
    case 6: 	// HDR SV (TS) AUXSV
        uat_decode_sv(frame, mdb);
        uat_decode_auxsv(frame, mdb);
        break;

    case 3: 	// HDR SV MS (TS)
        uat_decode_sv(frame, mdb);
        uat_decode_ms(frame, mdb);
        break;

    default:
        break;
    }
}

void uat_display_adsb_mdb(const struct uat_adsb_mdb *mdb, FILE *to)
{
    uat_display_hdr(mdb, to);
    uat_display_sv(mdb, to);
    uat_display_ms(mdb, to);
    uat_display_auxsv(mdb, to);
}

static void uat_decode_info_frame(struct uat_uplink_info_frame *frame)
{
    unsigned t_opt;

    frame->is_fisb = 0;

    if (frame->type != 0)
        return; // not FIS-B

    if (frame->length < 4) // too short for FIS-B
        return;

    t_opt = ((frame->data[1] & 0x01) << 1) | (frame->data[2] >> 7);

    switch (t_opt) {

    case 0: // Hours, Minutes
        frame->fisb.monthday_valid = 0;
        frame->fisb.seconds_valid = 0;
        frame->fisb.hours = (frame->data[2] & 0x7c) >> 2;
        frame->fisb.minutes = ((frame->data[2] & 0x03) << 4) | (frame->data[3] >> 4);
        frame->fisb.length = frame->length - 4;
        frame->fisb.data = frame->data + 4;
        break;

    case 1: // Hours, Minutes, Seconds
        if (frame->length < 5)
            return;
        frame->fisb.monthday_valid = 0;
        frame->fisb.seconds_valid = 1;
        frame->fisb.hours = (frame->data[2] & 0x7c) >> 2;
        frame->fisb.minutes = ((frame->data[2] & 0x03) << 4) | (frame->data[3] >> 4);
        frame->fisb.seconds = ((frame->data[3] & 0x0f) << 2) | (frame->data[4] >> 6);
        frame->fisb.length = frame->length - 5;
        frame->fisb.data = frame->data + 5;
        break;

    case 2: // Month, Day, Hours, Minutes
        if (frame->length < 5)
            return;
        frame->fisb.monthday_valid = 1;
        frame->fisb.seconds_valid = 0;
        frame->fisb.month = (frame->data[2] & 0x78) >> 3;
        frame->fisb.day = ((frame->data[2] & 0x07) << 2) | (frame->data[3] >> 6);
        frame->fisb.hours = (frame->data[3] & 0x3e) >> 1;
        frame->fisb.minutes = ((frame->data[3] & 0x01) << 5) | (frame->data[4] >> 3);
        frame->fisb.length = frame->length - 5; // ???
        frame->fisb.data = frame->data + 5;
        break;

    case 3: // Month, Day, Hours, Minutes, Seconds
        if (frame->length < 6)
            return;
        frame->fisb.monthday_valid = 1;
        frame->fisb.seconds_valid = 1;
        frame->fisb.month = (frame->data[2] & 0x78) >> 3;
        frame->fisb.day = ((frame->data[2] & 0x07) << 2) | (frame->data[3] >> 6);
        frame->fisb.hours = (frame->data[3] & 0x3e) >> 1;
        frame->fisb.minutes = ((frame->data[3] & 0x01) << 5) | (frame->data[4] >> 3);
        frame->fisb.seconds = ((frame->data[4] & 0x03) << 3) | (frame->data[5] >> 5);
        frame->fisb.length = frame->length - 6;
        frame->fisb.data = frame->data + 6;
        break;
    }

    frame->fisb.a_flag = (frame->data[0] & 0x80) ? 1 : 0;
    frame->fisb.g_flag = (frame->data[0] & 0x40) ? 1 : 0;
    frame->fisb.p_flag = (frame->data[0] & 0x20) ? 1 : 0;
    frame->fisb.product_id = ((frame->data[0] & 0x1f) << 6) | (frame->data[1] >> 2);
    frame->fisb.s_flag = (frame->data[1] & 0x02) ? 1 : 0;
    frame->is_fisb = 1;
}

void uat_decode_uplink_mdb(uint8_t *frame, struct uat_uplink_mdb *mdb)
{
    mdb->position_valid = (frame[5] & 0x01) ? 1 : 0;

    /* Even with position_valid = 0, there seems to be plausible data here.
     * Decode it always.
     */
    /*if (mdb->position_valid)*/

    uint32_t raw_lat = (frame[0] << 15) | (frame[1] << 7) | (frame[2] >> 1);
    uint32_t raw_lon = ((frame[2] & 0x01) << 23) | (frame[3] << 15) | (frame[4] << 7) | (frame[5] >> 1);
        
    mdb->lat = raw_lat * 360.0 / 16777216.0;
    if (mdb->lat > 90)
    	mdb->lat -= 180;
    mdb->lon = raw_lon * 360.0 / 16777216.0;
    if (mdb->lon > 180)
    	mdb->lon -= 360;

    mdb->utc_coupled = (frame[6] & 0x80) ? 1 : 0;
    mdb->app_data_valid = (frame[6] & 0x20) ? 1 : 0;
    mdb->slot_id = (frame[6] & 0x1f);
    mdb->tisb_site_id = (frame[7] >> 4);

    if (mdb->app_data_valid) {
        uint8_t *data, *end;

        memcpy(mdb->app_data, frame+8, 424);
        mdb->num_info_frames = 0;
        
        data = mdb->app_data;
        end = mdb->app_data + 424;
        while (mdb->num_info_frames < UPLINK_MAX_INFO_FRAMES && data+2 <= end) {
            struct uat_uplink_info_frame *frame = &mdb->info_frames[mdb->num_info_frames];
            frame->length = (data[0] << 1) | (data[1] >> 7);
            frame->type = (data[1] & 0x0f);
            if (data + frame->length + 2 > end) {
                // overrun?
                break;
            }

            if (frame->length == 0 && frame->type == 0) {
                break; // no more frames
            }

            frame->data = data + 2;

            uat_decode_info_frame(frame);

            data += frame->length + 2;
            ++mdb->num_info_frames;
        }
    }
}

static void display_generic_data(uint8_t *data, uint16_t length, FILE *to)
{
    unsigned i;

    fprintf(to, " Data:              ");
    for (i = 0; i < length; i += 16) {
        unsigned j;
        
        if (i > 0)
            fprintf(to, "                    ");
        
        for (j = i; j < i+16; ++j) {
            if (j < length)
                fprintf(to, "%02X ", data[j]);
            else
                fprintf(to, "   ");
        }
        
        for (j = i; j < i+16 && j < length; ++j) {
            fprintf(to, "%c", (data[j] >= 32 && data[j] < 127) ? data[j] : '.');
        }
        fprintf(to, "\n");
    }
}

// The odd two-string-literals here is to avoid \0x3ABCDEF being interpreted as a single (very large valued) character
static const char *dlac_alphabet = "\x03" "ABCDEFGHIJKLMNOPQRSTUVWXYZ\x1A\t\x1E\n| !\"#$%&'()*+,-./0123456789:;<=>?";

static const char *decode_dlac(uint8_t *data, unsigned bytelen, int rec_offset)

{
    static char buf[1024];
    bytelen = bytelen - rec_offset;
    uint8_t *end = data + bytelen;
    char *p = buf;
    int step = 0;
    int tab = 0;

    while (data < end) {
        int ch;

        assert(step >= 0 && step <= 3);
        switch (step) {
        case 0:
            ch = data[rec_offset] >> 2;
            ++data;
            break;
        case 1:
            ch = ((data[rec_offset-1] & 0x03) << 4) | (data[rec_offset] >> 4);
            ++data;
            break;
        case 2:
            ch = ((data[rec_offset-1] & 0x0f) << 2) | (data[rec_offset] >> 6);
            break;
        case 3:
            ch = data[rec_offset] & 0x3f;
            ++data;
            break;
        }

        if (tab) {
            while (ch > 0)
                *p++ = ' ', ch--;
            tab = 0;
        } else if (ch == 28) { // tab
            tab = 1;
        } else {
            *p++ = dlac_alphabet[ch];
        }

        step = (step+1)%4;
    }

    *p = 0;
    return buf;
}

static const char *get_fisb_product_name(uint16_t product_id)
{
    switch (product_id) {
    case 0:  case 20: return "METAR and SPECI";
    case 1:  case 21: return "TAF and Amended TAF";
    case 2:  case 22: return "SIGMET";
    case 3:  case 23: return "Convective SIGMET";
    case 4:  case 24: return "AIRMET";
    case 5:  case 25: return "PIREP";
    case 6:  case 26: return "AWW";
    case 7:  case 27: return "Winds and Temperatures Aloft";
    case 8:    	return "NOTAM (Including TFRs) and Service Status";
    case 9:    	return "Aerodrome and Airspace – D-ATIS";
    case 10:	return "Aerodrome and Airspace - TWIP";
    case 11:   	return "Aerodrome and Airspace - AIRMET";
    case 12:   	return "Aerodrome and Airspace - SIGMET/Convective SIGMET";
    case 13:   	return "Aerodrome and Airspace - SUA Status";
    case 14:   	return "G-AIRMET";
    case 15:   	return "Center Weather Advisory (CWAG)";
    case 51:   	return "National NEXRAD, Type 0 - 4 Level";
    case 52:   	return "National NEXRAD, Type 1 - 8 Level (Quasi 6-Level VIP)";
    case 53:   	return "National NEXRAD, Type 2 - 8 Level";
    case 54:   	return "National NEXRAD, Type 3 - 16 Level";
    case 55:   	return "Regional NEXRAD, Type 0 - Low Dynamic Range";
    case 56:   	return "Regional NEXRAD, Type 1 - 8 Level (Quasi 6-Level VIP)";
    case 57:   	return "Regional NEXRAD, Type 2 - 8 Level";
    case 58:   	return "Regional NEXRAD, Type 3 - 16 Level";
    case 59:   	return "Individual NEXRAD, Type 0 - Low Dynamic Range";
    case 60:   	return "Individual NEXRAD, Type 1 - 8 Level (quasi 6-Level VIP)";
    case 61:   	return "Individual NEXRAD, Type 2 - 8 Level";
    case 62:   	return "Individual NEXRAD, Type 3 - 16 Level";
    case 63:   	return "Global Block Representation - Regional NEXRAD, Type 4 - 8 Level";
    case 64:   	return "Global Block Representation - CONUS NEXRAD, Type 4 - 8 Level";
    case 70:   	return "Icing Forecast - Low";
    case 71:   	return "Icing Forecast - High";
    case 81:   	return "Radar Echo Tops Graphic, Scheme 1: 16-Level";
    case 82:   	return "Radar Echo Tops Graphic, Scheme 2: 8-Level";
    case 83:   	return "Storm Tops and Velocity";
    case 84:   	return "Cloud Tops";
    case 90:   	return "Turbulence Forecast - Low";
    case 91:   	return "Turbulence Forecast - High";
    case 101:  	return "Lightning Strike Type 1 (Pixel Level)";
    case 102:  	return "Lightning Strike Type 2 (Grid Element Level)";
    case 103:  	return "Lightning";
    case 151:  	return "Point Phenomena, Vector Format";
    case 201:  	return "Surface Conditions/Winter Precipitation Graphic";
    case 202:  	return "Surface Weather Systems";
    case 254:  	return "AIRMET, SIGMET: Bitmap Encoding";
    case 351:  	return "System Time";
    case 352:  	return "Operational Status";
    case 353:	return "Ground Station Status";
    case 401:  	return "Generic Raster Scan Data Product APDU Payload Format Type 1";
    case 402:  case 411: return "Generic Textual Data Product APDU Payload Format Type 1";
    case 403:  	return "Generic Vector Data Product APDU Payload Format Type 1";
    case 404:  case 412: return "Generic Symbolic Product APDU Payload Format Type 1";
    case 405:  case 413: return "Generic Textual Data Product APDU Payload Format Type 2";
    case 600:  	return "FISDL Products – Proprietary Encoding";
    case 2000: 	return "FAA/FIS-B Product 1 – Developmental";
    case 2001: 	return "FAA/FIS-B Product 2 – Developmental";
    case 2002: 	return "FAA/FIS-B Product 3 – Developmental";
    case 2003: 	return "FAA/FIS-B Product 4 – Developmental";
    case 2004: 	return "WSI Products - Proprietary Encoding";
    case 2005: 	return "WSI Developmental Products";
    default: 	return "Unknown";
    }
}

static const char *get_fisb_product_format(uint16_t product_id)
{
    switch (product_id) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: 
    case 351: case 352: case 353:
    case 402: case 405:
        return "Text";

    case 8: case 9: case 10: case 11: case 12: case 13 :case 14:
        return "Text/Graphic";
       
    case 20: case 21: case 22: case 23: case 24: case 25: case 26: case 27: 
    case 411: case 413:
        return "Text (DLAC)";

    case 51: 	case 52: case 53: case 54: case 55: case 56: case 57: case 58:
    case 59: 	case 60: case 61: case 62: case 63: case 64: case 70: case 71:
    case 81: 	case 82: case 83: case 84:
    case 90:    case 91:
    case 101: 	case 102: case 103: case 104:
    case 151:
    case 201: 	case 202:
    case 254:
    case 401:
    case 403:
    case 404:
        return "Graphic";

    case 412:
        return "Graphic (DLAC)";

    case 600: case 2004:
        return "Proprietary";

    case 2000: case 2001: case 2002: case 2003: case 2005: 
        return "Developmental";

    default:
        return "Unknown";
    }
}

static void uat_display_fisb_frame(const struct fisb_apdu *apdu, FILE *to)
{
	fprintf(to,"\nFIS-B: "
			" Flags:             %s%s%s%s "
			" Prod:  %u (%s) - %s\n",
			apdu->a_flag ? "A" : "",
            apdu->g_flag ? "G" : "",
            apdu->p_flag ? "P" : "",
            apdu->s_flag ? "S" : "",
            apdu->product_id,
            get_fisb_product_name(apdu->product_id),
            get_fisb_product_format(apdu->product_id));

    fprintf(to," PTime:");

    if (apdu->monthday_valid)
    	fprintf(to, "%u/%u ", apdu->month, apdu->day);
    fprintf(to, "%02u:%02u", apdu->hours, apdu->minutes);
    if (apdu->seconds_valid)
    	fprintf(to, ":%02u", apdu->seconds);
    fprintf(to, "\n");

    switch (apdu->product_id) {

    case 8:                //NOTAM
    {
    	int rec_offset =11; int recf;

    	recf = apdu->data[0];
    	fprintf(to," Record Format: %d \n",recf >> 4);
 //   	fprintf(filenotam," Record Fmt : %d \n",recf >> 4);
		uint16_t record_length=0; uint16_t report_number=0; uint16_t report_year=0;
		int overlay_record_identifier=0; int object_label=0; int object_label_flag=0;
		uint8_t object_type; uint8_t object_element;
		uint8_t object_status; uint8_t qualifier_flag;
		uint8_t param_flag; uint8_t record_applicability_options;
		uint8_t date_time_format; uint8_t element_flag;
		const char * object_labelt;
        char gstn[5];
		char ob_type_text[35]; char  ob_ele_text[35];
		int product_version;int record_count; int record_reference;
		const char * location_identifier;
		int geometry_overlay_options;
		int overlay_operator; int overlay_vertices_count;
		int d1;int d2;int d3;int d4;

        if ((recf >> 4) == 2 ) {             // text
        	rec_offset =11;
        	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
           	const char *report = text;
           	while (report) {
           		char report_buf[1024];
           		const char *next_report;
           		char *p, *r;

           		next_report = strchr(report, '\x1e'); // RS
           		if (!next_report)
           			next_report = strchr(report, '\x03'); // ETX
           		if (next_report) {
           			memcpy(report_buf, report, next_report - report);
           			report_buf[next_report - report] = 0;
           			report = next_report + 1;
           		} else {
           			strcpy(report_buf, report);
           			report = NULL;
           		}

           		if (!report_buf[0])
           			continue;

           		r = report_buf;
           		p = strchr(r, ' ');
           		if (p) {
           			*p = 0;
           			fprintf(to," Report Type:       %s\n",r);
           			fprintf(filenotam," Report Type: %s\n",r);
           			r = p+1;
           		}

           		p = strchr(r, '.');
           		if (p) {
           			*p = 0;

           			strncpy(gstn,r,5);
           			get_gs_name(gstn,reccount);
           			fprintf(to," RLoc:  %s - %s\n",gstn, gs_ret);
           			fprintf(filenotam," RLoc       : %s - %s\n",gstn, gs_ret);
           			r = p+1;
           		}

           		time_t current_time = time(NULL);
           		struct tm *tm = localtime(&current_time);
           		fprintf(filenotam," Time       : %s", asctime(tm));
           		fprintf(to,"\n%s \n",r);
           		fprintf(filenotam," Data:\n%s\n",r);
           		fflush(filenotam);
           	}
        }

        if ((recf >> 4) == 8){ //graphic
        	int datoff=6;
        	fprintf(to," Report Type:       NOTAM\n");
			fprintf(filenotam," Report Type: NOTAM\n");

    		product_version = ((apdu->data[0]) & 0x0F);
    		fprintf(to," Product Version: %d \n",product_version);
    		fprintf(filenotam," Product Version: %d \n",product_version);

    		record_count = ((apdu->data[1]) & 0xF0) >> 4;
    		fprintf(to," Record Count: %d \n",record_count);
    		fprintf(filenotam," Record Count: %d \n",record_count);

    		location_identifier = decode_dlac(apdu->data, 3, 2);
    		fprintf(to," Location ID: %s \n",location_identifier);
    		fprintf(filenotam," Location ID: %s \n",location_identifier);

    		record_reference = ((apdu->data[5]));
       		fprintf(to," Record Reference: %d \n",record_reference);
        	fprintf(filenotam," Record Reference: %d \n",record_reference);

        	rec_offset =2;
        	const char *text = decode_dlac(apdu->data,5 ,rec_offset);
            strncpy(gstn,text,5);
            get_gs_name(gstn,reccount);

            fprintf(to," RLoc:  %s - %s\n",gstn, gs_ret);
            fprintf(filenotam," RLoc       : %s - %s\n",gstn, gs_ret);

    		report_number = (((apdu->data[datoff + 1]) & 0x3F) << 8) | (apdu->data[datoff + 2]);
    		fprintf(to," Report Num : %d  ",report_number);
    		fprintf(filenotam," Report Num : %d  ",report_number);

    		record_length = ((apdu->data[datoff + 0]) << 2) | (((apdu->data[datoff + 1]) & 0xC0) >> 6);
    		fprintf(to,"Record Length: %d  ",record_length);
    		fprintf(filenotam,"Record Length: %d  ",record_length);

    		report_year = ((apdu->data[datoff + 3]) & 0xFE) >> 1;
    		fprintf(to,"Report Year: %d\n ",report_year);
    		fprintf(filenotam,"Report Year: %d\n ",report_year);

    		overlay_record_identifier = (((apdu->data[datoff + 4]) & 0x1E) >> 1) + 1; // Document instructs to add 1.
    		fprintf(to,"Ovrlay RcID: %d  ",overlay_record_identifier);
 			fprintf(filenotam,"Ovrlay RcID: %d  ",overlay_record_identifier);

 			object_label_flag = (apdu->data[datoff + 4] & 0x01);
 			fprintf(to, "Ob Lbl Fl: %d \n", object_label_flag);
 			fprintf(filenotam, "Ob Lbl Fl: %d \n", object_label_flag);

 			if (object_label_flag == 0) { // Numeric index.
 				object_label = ((apdu->data[datoff + 5]) << 8) | (apdu->data[datoff +6]);
 				fprintf(to, " Ob Lbl Num : %d  ", object_label);
 				fprintf(filenotam, " Ob Lbl Num : %d  ", object_label);
 				datoff = datoff +7;
 			} else {
 				object_labelt = decode_dlac(apdu->data,5, 2);
 			    fprintf(to, " Ob Lbl Alph: %s ", object_labelt);
 			    fprintf(filenotam, " Ob Lbl Alph: %s ", object_labelt);
 			    datoff = datoff + 14;
 			}

 			element_flag = ((apdu->data[datoff + 0]) & 0x80) >> 7;
 			fprintf(to," Elmnt Flag  : %d ", element_flag);
 			fprintf(filenotam, " Elmnt Flag  : %d  ", element_flag);

 			object_element = (apdu->data[datoff + 0]) & 0x1F;
 			fprintf(to, "Object Ele: %d\n", object_element);
 			fprintf(filenotam, "Object Ele: %d\n", object_element);

 			object_status = (apdu->data[datoff +1]) & 0x0F;
 			fprintf(to, " Object Stat: %d  ", object_status);
 			fprintf(filenotam, " Object Stat: %d ", object_status);

 			object_type = (apdu->data[datoff +1] & 0xF0) >> 4;
 			fprintf(to, " Object Type: %d \n", object_type);
 			fprintf(filenotam, " Object Type: %d \n", object_type);

 			qualifier_flag = ((apdu->data[datoff + 0]) & 0x40) >> 6;
 			fprintf(to, " Qualif Flag: %d  ", qualifier_flag);
 			fprintf(filenotam, " Qualif Flag: %d  ", qualifier_flag);

 			param_flag = ((apdu->data[datoff + 0]) & 0x20) >> 5;
 			fprintf(to, "Param Flag: %d \n", param_flag);
 			fprintf(filenotam, "Param Flag: %d \n", param_flag);

 			if (qualifier_flag == 0){
 				datoff = datoff + 2;
 			}

			geometry_overlay_options = (apdu->data[datoff + 0]) & 0x0F;
 			fprintf(to, " Geo Overlay Options: %d  ", geometry_overlay_options);
 			fprintf(filenotam, " Geo Overlay Options: %d  ", geometry_overlay_options);

 			overlay_operator = ((apdu->data[datoff +1]) & 0xC0) >> 6;
 			fprintf(to, "Overlay Operator: %d  ", overlay_operator);
 			fprintf(filenotam, "Overlay Operator: %d  ", overlay_operator);

			overlay_vertices_count = ((apdu->data[datoff +1]) & 0x3F) + 1; // Document instructs to add 1. (6.20).
 			fprintf(to, "Overlay vertices count: %d \n", overlay_vertices_count);
 			fprintf(filenotam, "Overlay vertices count: %d \n", overlay_vertices_count);

 			record_applicability_options = ((apdu->data[datoff + 0]) & 0xC0) >> 6;
 			date_time_format = ((apdu->data[datoff + 0]) & 0x30) >> 4;

 			fprintf(to, " Rec App Opt: %d  ", record_applicability_options);
 			fprintf(filenotam, " Rec App Opt: %d  ", record_applicability_options);

 			fprintf(to, "Rec App Date: %d \n", date_time_format );
 			fprintf(filenotam, "Rec App Date: %d \n", date_time_format );

 			switch (record_applicability_options) {
 			case 0:  // No times given. UFN.  (record_data[2:], date_time_format)
 				fprintf(to, "NO Dates Given\n");
 				fprintf(filenotam, "No Dates Given\n");
 				datoff = datoff +2;
 				break;

 			case 1:  // Start time only. WEF.
 	 			d1 = apdu->data[datoff + 2];
 	 			d2 = apdu->data[datoff + 3];
 	 			d3 = apdu->data[datoff + 4];
 	 			d4 = apdu->data[datoff + 5];
 	 			fprintf(to, " Only Start Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			fprintf(filenotam, " Only Start Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			datoff = datoff + 6;
 			break;

 			case 2: // End time only. TIL.
 				d1 = apdu->data[datoff + 2];
 				d2 = apdu->data[datoff + 3];
 				d3 = apdu->data[datoff + 4];
 				d4 = apdu->data[datoff + 5];
 				fprintf(to, " Only End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 				fprintf(filenotam, " Only End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 				datoff = datoff + 6;
 				break;

 			case 3: // Both start and end times. WEF.
 				d1 = apdu->data[datoff + 2];
 	 			d2 = apdu->data[datoff + 3];
 	 			d3 = apdu->data[datoff + 4];
 	 			d4 = apdu->data[datoff + 5];
 	 			fprintf(to, " Start Date : %02d/%02d %02d:%02d  ",d1,d2,d3,d4);
 	 			fprintf(filenotam, " Start Date : %02d/%02d %02d:%02d  ",d1,d2,d3,d4);
 				d1 = apdu->data[datoff + 6];
 	 			d2 = apdu->data[datoff + 7];
 	 			d3 = apdu->data[datoff + 8];
 	 			d4 = apdu->data[datoff + 9];
 	 			fprintf(to, "End Date:%02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			fprintf(filenotam, "End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			datoff = datoff + 10;
 				break;
 			}

 			strcpy(ob_type_text,"Unknown object");
 			strcpy(ob_ele_text,"Unknown Element");

 			if (object_label_flag == 0 && object_type==14){
 				strcpy(ob_type_text,"Airspace");
 				if (element_flag==1){
 					strcpy(ob_ele_text,object_element_names[object_element]);
 				}
 			}

 		    uint32_t lat_raw ;  uint32_t lng_raw;  uint32_t alt_raw;  int alt;
 		    float lat ;  float lng;
 		    float fct_f =0.000687; // float_t fct_t =0.001373;
 			switch (geometry_overlay_options) {

 			case 9: // Extended Range 3D Point (AGL). p.47.
 				if (record_length < 6) {
 	 	 			fprintf(to, "Too short\n");
 	 	 			fprintf(filenotam,  "Too short\n");
 				}
 				else {
 					lng_raw = ((apdu->data[datoff +0]) << 11) | ((apdu->data[datoff +1]) << 3) | ((apdu->data[datoff +2]) & 0xE0 >> 5);
 					lat_raw = (((apdu->data[datoff +2]) & 0x1F) << 14) | ((apdu->data[datoff + 3]) << 6) | (((apdu->data[datoff + 4]) & 0xFC) >> 2);
 					alt_raw = (((apdu->data[datoff + 4]) & 0x03) << 8) | (apdu->data[datoff + 5]);

 					lat = fct_f * lat_raw;
 					lng = fct_f * lng_raw;
 					if (lat > 90.0) {
 						lat = lat - 180.0;}
 					if (lng > 180.0) {
 						lng = lng - 360.0;

 					alt = alt_raw * 100;

 					fprintf(to, " Coord      : %f,%f\n", lat, lng);
 					fprintf(filenotam, " Coord      : %f,%f  Alt: %d\n", lat, lng, alt);
 					}
 				}
 				break;
 			}

 			fprintf(to, " Object Type: %s  Object Element: %s\n",ob_type_text,ob_ele_text);
 			fprintf(filenotam, " Object Type: %s  Object Element: %s\n",ob_type_text,ob_ele_text);
 			fprintf(to, "\n");
 			fprintf(filenotam,"\n");
 			display_generic_data(apdu->data, apdu->length, to);
        }
    }
    break;

    case 11:                      //AIRMET
    {
    	int rec_offset=11;
    	char gstn[5]; int recf;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;
		uint16_t record_length=0; uint16_t report_number=0; uint16_t report_year=0;
		int overlay_record_identifier=0; int object_label=0; int object_label_flag=0;
		uint8_t object_type; uint8_t object_element;
		uint8_t object_status; uint8_t qualifier_flag;
		uint8_t param_flag; uint8_t record_applicability_options;
		uint8_t date_time_format; uint8_t element_flag;
		const char * object_labelt;
		char ob_type_text[35]; char  ob_ele_text[35];
		int product_version;int record_count; int record_reference;
		const char * location_identifier;
		int geometry_overlay_options;
		int overlay_operator; int overlay_vertices_count;
		int d1;int d2;int d3;int d4;

		recf = apdu->data[0];
    	fprintf(to,"\n Record Fmt : %d \n",recf >> 4);
    	fprintf(fileairmet,"\n Record Fmt : %d \n",recf >> 4);

    	if ((recf >> 4) == 8){ //graphic
    		int datoff=6;

			fprintf(to," Report Type:       AIRMET\n");
			fprintf(fileairmet," Report Type: AIRMET\n");

    		product_version = ((apdu->data[0]) & 0x0F);
    		fprintf(to," Product Version: %d \n",product_version);
    		fprintf(fileairmet," Product Version: %d \n",product_version);

    		record_count = ((apdu->data[1]) & 0xF0) >> 4;
    		fprintf(to," Record Count: %d \n",record_count);
    		fprintf(fileairmet," Record Count: %d \n",record_count);

    		location_identifier = decode_dlac(apdu->data, 3, 2);

//		decode_dlac(apdu->data,5, 2);

    		fprintf(to," Location ID: %s \n",location_identifier);
    		fprintf(fileairmet," Location ID: %s \n",location_identifier);

    		record_reference = ((apdu->data[5]));
    				//FIXME: Special values. 0x00 means "use location_identifier".
    		//0xFF means "use different reference". (4-3).
       		fprintf(to," Record Reference: %d \n",record_reference);
       		fprintf(fileairmet," Record Reference: %d \n",record_reference);

        	rec_offset =2;
            const char *text = decode_dlac(apdu->data,5 ,rec_offset);
            strncpy(gstn,text,5);
            get_gs_name(gstn,reccount);

            fprintf(to," RLoc:  %s - %s\n",gstn, gs_ret);
            fprintf(fileairmet," RLoc       : %s - %s\n",gstn, gs_ret);

    		report_number = (((apdu->data[datoff + 1]) & 0x3F) << 8) | (apdu->data[datoff + 2]);
    		fprintf(to," Report Num : %d  ",report_number);
    		fprintf(fileairmet," Report Num : %d  ",report_number);

    		record_length = ((apdu->data[datoff + 0]) << 2) | (((apdu->data[datoff + 1]) & 0xC0) >> 6);
    		fprintf(to,"Record Length: %d ",record_length);
    		fprintf(fileairmet,"Record Length: %d ",record_length);

    		report_year = ((apdu->data[datoff + 3]) & 0xFE) >> 1;
    		fprintf(to,"Report Year: %d\n ",report_year);
    		fprintf(fileairmet,"Report Year: %d\n ",report_year);

    		overlay_record_identifier = (((apdu->data[datoff + 4]) & 0x1E) >> 1) + 1; // Document instructs to add 1.
    		fprintf(to,"Ovrlay RcID: %d  ",overlay_record_identifier);
 			fprintf(fileairmet,"Ovrlay RcID: %d  ",overlay_record_identifier);

 			object_label_flag = (apdu->data[datoff + 4] & 0x01);
 			fprintf(to, "Ob Lbl Fl: %d \n", object_label_flag);
 			fprintf(fileairmet, "Ob Lbl Fl: %d \n", object_label_flag);
 			if (object_label_flag == 0) { // Numeric index.
 				object_label = ((apdu->data[datoff + 5]) << 8) | (apdu->data[datoff +6]);
 				fprintf(to, " Ob Lbl Num : %d  ", object_label);
 				fprintf(fileairmet, " Ob Lbl Num : %d  ", object_label);
 				datoff = datoff +7;
 			} else {
 				object_labelt = decode_dlac(apdu->data,5, 2);
 			    fprintf(to, " Ob Lbl Alph: %s ", object_labelt);
 			    fprintf(fileairmet, " Ob Lbl Alph: %s ", object_labelt);
 			    datoff = datoff + 14;
 			}

 			element_flag = ((apdu->data[datoff + 0]) & 0x80) >> 7;
 			fprintf(to," Elmnt Flag  : %d ", element_flag);
 			fprintf(fileairmet, " Elmnt Flag  : %d  ", element_flag);

 			object_element = (apdu->data[datoff + 0]) & 0x1F;
 			fprintf(to, "Object Ele: %d\n", object_element);
 			fprintf(fileairmet, "Object Ele: %d\n", object_element);

 			object_status = (apdu->data[datoff +1]) & 0x0F;
 			fprintf(to, " Object Stat: %d  ", object_status);
 			fprintf(fileairmet, " Object Stat: %d  ", object_status);

 			object_type = (apdu->data[datoff +1] & 0xF0) >> 4;
 			fprintf(to, " Object Type: %d \n", object_type);
 			fprintf(fileairmet, " Object Type: %d \n", object_type);

 			qualifier_flag = ((apdu->data[datoff + 0]) & 0x40) >> 6;
 			fprintf(to, " Qualif Flag: %d  ", qualifier_flag);
 			fprintf(fileairmet, " Qualif Flag: %d  ", qualifier_flag);

 			param_flag = ((apdu->data[datoff + 0]) & 0x20) >> 5;
 			fprintf(to, "Param Flag: %d \n", param_flag);
 			fprintf(fileairmet, "Param Flag: %d \n", param_flag);

 			if (qualifier_flag == 0){
 				datoff = datoff + 2;
 			}

 			geometry_overlay_options = (apdu->data[datoff + 0]) & 0x0F;
 			fprintf(to, " Geo Overlay Options: %d  ", geometry_overlay_options);
 			fprintf(fileairmet, " Geo Overlay Options: %d  ", geometry_overlay_options);

 			overlay_operator = ((apdu->data[datoff +1]) & 0xC0) >> 6;
 			fprintf(to, "Overlay Operator: %d  ", overlay_operator);
 			fprintf(fileairmet, "Overlay Operator: %d  ", overlay_operator);

			overlay_vertices_count = ((apdu->data[datoff +1]) & 0x3F) + 1; // Document instructs to add 1. (6.20).
 			fprintf(to, "Overlay vertices count: %d \n", overlay_vertices_count);
 			fprintf(fileairmet, "Overlay vertices count: %d \n", overlay_vertices_count);

 			record_applicability_options = ((apdu->data[datoff + 0]) & 0xC0) >> 6;
 			date_time_format = ((apdu->data[datoff + 0]) & 0x30) >> 4;

 			fprintf(to, " Rec App Opt: %d  ", record_applicability_options);
 			fprintf(fileairmet, " Rec App Opt: %d  ", record_applicability_options);

 			fprintf(to, "Rec App Date: %d \n", date_time_format );
 			fprintf(fileairmet, "Rec App Date: %d \n", date_time_format );

 			switch (record_applicability_options) {
 			case 0:  // No times given. UFN.  (record_data[2:], date_time_format)
 				fprintf(to, "NO Dates Given\n");
 				fprintf(fileairmet, "No Dates Given\n");
 				datoff = datoff +2;
 				break;

 			case 1:  // Start time only. WEF.
 	 			d1 = apdu->data[datoff + 2];
 	 			d2 = apdu->data[datoff + 3];
 	 			d3 = apdu->data[datoff + 4];
 	 			d4 = apdu->data[datoff + 5];

 	 			fprintf(to, " Only Start Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			fprintf(fileairmet, " Only Start Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			datoff = datoff + 6;
 			break;

 			case 2: // End time only. TIL.
 				d1 = apdu->data[datoff + 2];
 				d2 = apdu->data[datoff + 3];
 				d3 = apdu->data[datoff + 4];
 				d4 = apdu->data[datoff + 5];

 				fprintf(to, " Only End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 				fprintf(fileairmet, " Only End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);

 				datoff = datoff + 6;

 				break;

 			case 3: // Both start and end times. WEF.
 				d1 = apdu->data[datoff + 2];
 	 			d2 = apdu->data[datoff + 3];
 	 			d3 = apdu->data[datoff + 4];
 	 			d4 = apdu->data[datoff + 5];

 	 			fprintf(to, " Start Date : %02d/%02d %02d:%02d  ",d1,d2,d3,d4);
 	 			fprintf(fileairmet, " Start Date : %02d/%02d %02d:%02d  ",d1,d2,d3,d4);

 				d1 = apdu->data[datoff + 6];
 	 			d2 = apdu->data[datoff + 7];
 	 			d3 = apdu->data[datoff + 8];
 	 			d4 = apdu->data[datoff + 9];

 	 			fprintf(to, "End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			fprintf(fileairmet, "End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);

 	 			datoff = datoff + 10;
 				break;
 			}

 			strcpy(ob_type_text,"Unknown object");
 			strcpy(ob_ele_text,"Unknown Element");
 			if (object_label_flag == 0 && object_type==14){
 				strcpy(ob_type_text,"Airspace");
 				if (element_flag==1){
 					strcpy(ob_ele_text,object_element_names[object_element]);
 				}
 			}
 		    uint32_t lat_raw ;  uint32_t lng_raw;  uint32_t alt_raw;  int alt;
 		    float lat ;  float lng;  float fct_f =0.000687;     // float_t fct_t =0.001373;

 			switch (geometry_overlay_options) {
 			case 3: // Extended Range 3D Polygon (MSL).
// 				points = make([]GeoPoint, 0) // Slice containing all of the points.
// 				fmt.Fprintf(ioutil.Discard, "%d\n", len(record_data))
 				for (int i = 0; i < overlay_vertices_count; i++) {
 					lng_raw = ((apdu->data[datoff + i]) << 11) | ((apdu->data[datoff +i+1]) << 3) | ((apdu->data[datoff +i+2]) & 0xE0 >> 5);
 					lat_raw = (((apdu->data[datoff +i+2]) & 0x1F) << 14) | ((apdu->data[datoff +i+3]) << 6) | (((apdu->data[datoff +i+4]) & 0xFC) >> 2);
 					alt_raw = (((apdu->data[datoff +i+4]) & 0x03) << 8) | (apdu->data[datoff +i+5]);

 					datoff = datoff + 5;

// 					fprintf(to,"lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);
// 					fprintf(fileairmet,"lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);

 					lat = fct_f * lat_raw;
 					lng = fct_f * lng_raw;
 					if (lat > 90.0) {
 						lat = lat - 180.0;}
 					if (lng > 180.0) {
 						lng = lng - 360.0;
	}
 					alt = alt_raw * 100;
 //					fprintf(to, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(to, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);
 //					fprintf(fileairmet, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(fileairmet, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);

 }
// 					var point GeoPoint
// 					point.Lat = lat
// 					point.Lon = lng
// 					point.Alt = alt
// 					points = append(points, point)
// 					f.Points = points

    	break;

 			case 9: // Extended Range 3D Point (AGL). p.47.
 				if (record_length < 6) {
 	 	 			fprintf(to, "Too short\n");
 	 	 			fprintf(fileairmet,  "Too short\n");
 				}
 				else {
 					lng_raw = ((apdu->data[datoff +0]) << 11) | ((apdu->data[datoff +1]) << 3) | ((apdu->data[datoff +2]) & 0xE0 >> 5);
 					lat_raw = (((apdu->data[datoff +2]) & 0x1F) << 14) | ((apdu->data[datoff + 3]) << 6) | (((apdu->data[datoff + 4]) & 0xFC) >> 2);
 					alt_raw = (((apdu->data[datoff + 4]) & 0x03) << 8) | (apdu->data[datoff + 5]);

 //					fprintf(to, "lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);
// 					fprintf(fileairmet, "lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);

 					lat = fct_f * lat_raw;
 					lng = fct_f * lng_raw;
 					if (lat > 90.0) {
 						lat = lat - 180.0; }
 					if (lng > 180.0) {
 						lng = lng - 360.0;

 					alt = alt_raw * 100;
 //					fprintf(to, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
// 					fprintf(fileairmet, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(to, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);
 					fprintf(fileairmet, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);
 					}
 				}
 				break;
 			}
 			fprintf(to, " Object Type: %s  Object Element: %s\n",ob_type_text,ob_ele_text);
 			fprintf(fileairmet, " Object Type: %s  Object Element: %s\n",ob_type_text,ob_ele_text);
    	}

    	if ((recf >> 4) == 2 ) {             // text

    		while (report) {
    			char report_buf[1024];
    			const char *next_report;
    			char *p, *r;

    			next_report = strchr(report, '\x1e'); // RS
    			if (!next_report)
    				next_report = strchr(report, '\x03'); // ETX
    			if (next_report) {
    				memcpy(report_buf, report, next_report - report);
    				report_buf[next_report - report] = 0;
    				report = next_report + 1;
    			} else {
    				strcpy(report_buf, report);
    				report = NULL;
    				}
    			if (!report_buf[0])
    				continue;
    			r = report_buf;
    			p = strchr(r, ' ');
    			if (p) {
    				*p = 0;
    				fprintf(to," Report Type:       %s\n",r);
    				fprintf(fileairmet," Report Type: %s\n",r);
    				r = p+1;
    			}
    			p = strchr(r, ' ');
    			if (p) {
    				*p = 0;
    				strncpy(gstn,r,5);
    				get_gs_name(gstn,reccount);
    				fprintf(to," RLoc:  %s - %s\n",gstn, gs_ret);
    				fprintf(fileairmet," RLoc       : %s - %s\n",gstn, gs_ret);
    				r = p+1;
    			}

    			time_t current_time = time(NULL);
    			struct tm *tm = localtime(&current_time);
    			fprintf(fileairmet," Time       : %s", asctime(tm));
    			report_number = (apdu->data[8] << 6) | (apdu->data[9] & 0xFC >> 2);
    			fprintf(to," Report Num : %d \n",report_number);
    			fprintf(fileairmet," Report Num : %d \n",report_number);

    			fprintf(to,"\n%s \n",r);
    			fprintf(fileairmet," Data:\n");
    			fprintf(fileairmet,"%s\n",r);
    		}
    	}
    	else {
    		display_generic_data(apdu->data, apdu->length, to);   }

		fflush(fileairmet);
    }
    break;

    case 12:                      //SIGMET
    {
    	int rec_offset=11; int recf;
    	char gstn[5];

    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	recf = apdu->data[0];
    	fprintf(to," Record Fmt  : %d \n",recf >> 4);
    	if ((recf >> 4) == 2 ) {             // text
    		while (report) {
    			char report_buf[1024];
    			const char *next_report;
    			char *p, *r;

    			next_report = strchr(report, '\x1e'); // RS
    			if (!next_report)
    				next_report = strchr(report, '\x03'); // ETX
    			if (next_report) {
    				memcpy(report_buf, report, next_report - report);
    				report_buf[next_report - report] = 0;
    				report = next_report + 1;
    			} else {
    				strcpy(report_buf, report);
    				report = NULL;
    				}
    			if (!report_buf[0])
    				continue;
    			r = report_buf;
    			p = strchr(r, ' ');
    			if (p) {
    				*p = 0;
    				fprintf(to," Report Type:       %s\n",r);
    				fprintf(filesigmet," Report Type : %s\n",r);
    				r = p+1;
    			}
    			p = strchr(r, ' ');
    			if (p) {
    				*p = 0;
    				strncpy(gstn,r,5);
    				get_gs_name(gstn,reccount);
    				fprintf(to," RLoc:  %s - %s\n",gstn, gs_ret);
    				fprintf(filesigmet," RLoc        : %s - %s\n",gstn, gs_ret);
    				r = p+1;
    			}
    			time_t current_time = time(NULL);
    			struct tm *tm = localtime(&current_time);
    			fprintf(filesigmet," Time        : %s", asctime(tm));
    			fprintf(to,"\n%s \n",r);
    			fprintf(filesigmet," Data:\n");
    			fprintf(filesigmet,"%s\n",r);
    			fflush(filesigmet);
    		}
    	}
    	else
    		display_generic_data(apdu->data, apdu->length, to);
    }
    break;

    case 13:                  //SUA
    {
    	int rec_offset=11;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	display_generic_data(apdu->data, apdu->length, to);

    	while (report) {
    		char report_buf[1024];
    		const char *next_report;
    		char *p, *r;
    		char *sua_text;

    		next_report = strchr(report, '\x1e'); // RS
    		if (!next_report)
    			next_report = strchr(report, '\x03'); // ETX
    		if (next_report) {
    			memcpy(report_buf, report, next_report - report);
    			report_buf[next_report - report] = 0;
    			report = next_report + 1;
    		} else {
    			strcpy(report_buf, report);
    			report = NULL;
    			}
    		if (!report_buf[0])
    			continue;

    		r = report_buf;
    		p = strchr(r, ' ');
    		if (p) {
    			*p = 0;
    		 	time_t current_time = time(NULL);
    		 	char * tm=ctime(&current_time);
    		    tm[strlen(tm)-1] = '\0';
        		fprintf(filesua," Time           : %s\n", tm);
    			fprintf(to," Report Type:       %s\n",r);
    			fprintf(filesua," Report Type    : %s\n",r);
    			r = p+1;
    		}
    		p = strchr(r, ' ');
    		if (p) {
    			*p = 0;
    			fprintf(to," Report time:       %sZ\n",r);
    			fprintf(filesua," Report time    : %sZ\n",r);
    			r = p+1;
    		}

			sua_text = (char *)malloc(strlen(r) + 1);
			strcpy(sua_text,r);

			get_sua_text(sua_text,to);

    		fprintf(to,"\n%s \n",r);
    	}
    }
    break;

    case 14:     //G-AIRMET
    {

//    	int rec_offset=11;
//    	char gstn[5];
    	int recf;
		uint16_t record_length=0; 	uint16_t report_number=0;uint16_t report_year=0;
		int overlay_record_identifier=0; int object_label=0; int object_label_flag=0;
		uint8_t object_type; uint8_t object_element;
		uint8_t object_status; uint8_t qualifier_flag;
		uint8_t param_flag;
		uint8_t record_applicability_options;
		uint8_t date_time_format; uint8_t element_flag;
		char ob_type_text[35]; char  ob_ele_text[35];

		const char * object_labelt;

		int product_version;int record_count; int record_reference;
		const char * location_identifier;
		int geometry_overlay_options;
		int overlay_operator; int overlay_vertices_count;
		int d1;int d2;int d3;int d4;

    	recf = apdu->data[0];

    	fprintf(to," Record Fmt : %d \n",recf >> 4);

    	if ((recf >> 4) == 8){ //graphic
        	int datoff=6;
    		fprintf(to,"\n Report Type:       G-AIRMET\n");
    		fprintf(filegairmet,"\n Report Type: G-AIRMET\n");

    		product_version = ((apdu->data[0]) & 0x0F);
    		fprintf(to," Product Version %d \n",product_version);
    		fprintf(filegairmet," Product Version %d \n",product_version);

    		record_count = ((apdu->data[1]) & 0xF0) >> 4;
    		fprintf(to," Record Count: %d \n",record_count);
    		fprintf(filegairmet," Rrecord Count: %d \n",record_count);

    		location_identifier = decode_dlac(apdu->data, 3, 2);
    		fprintf(to," Location ID: %s \n",location_identifier);
    		fprintf(filegairmet," Location ID: %s \n",location_identifier);

    		record_reference = ((apdu->data[5]));
    				//FIXME: Special values. 0x00 means "use location_identifier".
    				//0xFF means "use different reference". (4-3).
       		fprintf(to," Record Reference : %d \n",record_reference);
       		fprintf(filegairmet," Record Reference: %d \n",record_reference);

    		time_t current_time = time(NULL);
    		struct tm *tm = localtime(&current_time);
    		fprintf(filegairmet," Time       : %s", asctime(tm));

    		report_number = (((apdu->data[datoff + 1]) & 0x3F) << 8) | (apdu->data[datoff + 2]);
    		fprintf(to," Report Num : %d  ",report_number);
    		fprintf(filegairmet," Report Num : %d  ",report_number);

    		record_length = ((apdu->data[datoff + 0]) << 2) | (((apdu->data[datoff + 1]) & 0xC0) >> 6);
    		fprintf(to,"Record Length: %d ",record_length);
    		fprintf(filegairmet,"Record Length: %d ",record_length);

    		report_year = ((apdu->data[datoff + 3]) & 0xFE) >> 1;
    		fprintf(to,"Report Year: %d\n ",report_year);
    		fprintf(filegairmet,"Report Year: %d\n ",report_year);

    		overlay_record_identifier = (((apdu->data[datoff + 4]) & 0x1E) >> 1) + 1; // Document instructs to add 1.
    		fprintf(to,"Ovrlay RcID: %d  ",overlay_record_identifier);
 			fprintf(filegairmet,"Ovrlay RcID: %d  ",overlay_record_identifier);

 			object_label_flag = (apdu->data[datoff + 4] & 0x01);
 			fprintf(to, "Ob Lbl Fl: %d \n", object_label_flag);
 			fprintf(filegairmet, "Ob Lbl Fl: %d \n", object_label_flag);

 			if (object_label_flag == 0) { // Numeric index.
 				object_label = ((apdu->data[datoff + 5]) << 8) | (apdu->data[datoff +6]);
 				fprintf(to, " Ob Lbl Num : %d  ", object_label);
 				fprintf(filegairmet, " Ob Lbl Num : %d  ", object_label);
 				datoff = datoff +7;
 			} else {
 				object_labelt = decode_dlac(apdu->data,5, 2);
 				fprintf(to, " Ob Lbl Alph: %s ", object_labelt);
 			    fprintf(filegairmet, " Ob Lbl Alph: %s ", object_labelt);
 			   datoff = datoff + 14;
 			}

 			element_flag = ((apdu->data[datoff + 0]) & 0x80) >> 7;
 			fprintf(to," Elmnt Flag  : %d ", element_flag);
 			fprintf(filegairmet, " Elmnt Flag  : %d  ", element_flag);

 			object_element = (apdu->data[datoff + 0]) & 0x1F;
 			fprintf(to, "Object Ele: %d\n", object_element);
 			fprintf(filegairmet, "Object Ele: %d\n", object_element);

 			object_status = (apdu->data[datoff +1]) & 0x0F;
 			fprintf(to, " Object Stat: %d  ", object_status);
 			fprintf(filegairmet, " Object Stat: %d  ", object_status);

 			object_type = (apdu->data[datoff +1] & 0xF0) >> 4;
 			fprintf(to, " Object Type: %d \n", object_type);;
 			fprintf(filegairmet, " Object Type: %d \n", object_type);

 			qualifier_flag = ((apdu->data[datoff + 0]) & 0x40) >> 6;
 			fprintf(to, " Qualif Flag: %d  ", qualifier_flag);
 			fprintf(filegairmet, " Qualif Flag: %d  ", qualifier_flag);

 			param_flag = ((apdu->data[datoff + 0]) & 0x20) >> 5;
 			fprintf(to, "Param Flag: %d \n", param_flag);
 			fprintf(filegairmet, "Param Flag: %d \n", param_flag);

 			if (qualifier_flag == 0){
 				datoff = datoff + 2;
 			}

			geometry_overlay_options = (apdu->data[datoff + 0]) & 0x0F;
 			fprintf(to, " Geo Overlay Options: %d  ", geometry_overlay_options);
 			fprintf(filegairmet, " Geo Overlay Options: %d  ", geometry_overlay_options);

 			overlay_operator = ((apdu->data[datoff +1]) & 0xC0) >> 6;
 			fprintf(to, "Overlay Operator: %d  ", overlay_operator);
 			fprintf(filegairmet, "Overlay Operator: %d  ", overlay_operator);

			overlay_vertices_count = ((apdu->data[datoff +1]) & 0x3F) + 1; // Document instructs to add 1. (6.20).
 			fprintf(to, "Overlay vertices count: %d \n", overlay_vertices_count);
 			fprintf(filegairmet, "Overlay vertices count: %d \n", overlay_vertices_count);

 			record_applicability_options = ((apdu->data[datoff + 0]) & 0xC0) >> 6;
 			date_time_format = ((apdu->data[datoff + 0]) & 0x30) >> 4;

 			fprintf(to, " Rec App Opt: %d  ", record_applicability_options);
 			fprintf(filegairmet, " Rec App Opt: %d  ", record_applicability_options);

 			fprintf(to, "Rec App Date: %d \n", date_time_format );
 			fprintf(filegairmet, "Rec App Date: %d \n", date_time_format );

 			switch (record_applicability_options) {
 			case 0:  // No times given. UFN.  (record_data[2:], date_time_format)
 				fprintf(to, "NO Dates Given\n");
 				fprintf(filegairmet, "No Dates Given\n");
 				datoff = datoff +2;
 				break;

 			case 1:  // Start time only. WEF.
 	 			d1 = apdu->data[datoff + 2];
 	 			d2 = apdu->data[datoff + 3];
 	 			d3 = apdu->data[datoff + 4];
 	 			d4 = apdu->data[datoff + 5];

 	 			fprintf(to, " Only Start Date: %02d/%02d %02d:%02d\n",d1,d2,d3,d4);
 	 			fprintf(filegairmet, " Only Start Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			datoff = datoff + 6;
 			break;

 			case 2: // End time only. TIL.
 				d1 = apdu->data[datoff + 2];
 				d2 = apdu->data[datoff + 3];
 				d3 = apdu->data[datoff + 4];
 				d4 = apdu->data[datoff + 5];

 				fprintf(to, " Only End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 				fprintf(filegairmet, " Only End Date:%02d/%02d %02d:%02d \n",d1,d2,d3,d4);

 				datoff = datoff + 6;

 				break;

 			case 3: // Both start and end times. WEF.
 				d1 = apdu->data[datoff + 2];
 	 			d2 = apdu->data[datoff + 3];
 	 			d3 = apdu->data[datoff + 4];
 	 			d4 = apdu->data[datoff + 5];

 	 			fprintf(to, " Start Date : %02d/%02d %02d:%02d  ",d1,d2,d3,d4);
 	 			fprintf(filegairmet, " Start Date : %02d/%02d %02d:%02d  ",d1,d2,d3,d4);

 				d1 = apdu->data[datoff + 6];
 	 			d2 = apdu->data[datoff + 7];
 	 			d3 = apdu->data[datoff + 8];
 	 			d4 = apdu->data[datoff + 9];

 	 			fprintf(to, "End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);
 	 			fprintf(filegairmet, "End Date: %02d/%02d %02d:%02d \n",d1,d2,d3,d4);

 	 			datoff = datoff + 10;
 				break;
 			}

 			strcpy(ob_type_text,"Unknown object");
 			strcpy(ob_ele_text,"Unknown Element");
 			if (object_label_flag == 0 && object_type==14){
 				strcpy(ob_type_text,"Airspace");
 				if (element_flag==1){
 					strcpy(ob_ele_text,object_element_names[object_element]);
 				}
 			}
 		    uint32_t lat_raw ;  uint32_t lng_raw;  uint32_t alt_raw;  int alt;
 		    float lat ;  float lng;
 		    float fct_f =0.000687; // float_t fct_t =0.001373;

 		    switch (geometry_overlay_options) {

 		    case 3: // Extended Range 3D Polygon (MSL).
// 				points = make([]GeoPoint, 0) // Slice containing all of the points.
// 				fmt.Fprintf(ioutil.Discard, "%d\n", len(record_data))
 		    	for (int i = 0; i < overlay_vertices_count; i++) {
 		    		lng_raw = ((apdu->data[datoff + i]) << 11) | ((apdu->data[datoff +i+1]) << 3) | ((apdu->data[datoff +i+2]) & 0xE0 >> 5);
 					lat_raw = (((apdu->data[datoff +i+2]) & 0x1F) << 14) | ((apdu->data[datoff +i+3]) << 6) | (((apdu->data[datoff +i+4]) & 0xFC) >> 2);
 					alt_raw = (((apdu->data[datoff +i+4]) & 0x03) << 8) | (apdu->data[datoff +i+5]);

 					datoff = datoff + 5;

// 					fprintf(to,"lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);
// 					fprintf(fileairmet,"lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);

 					lat = fct_f * lat_raw;
 					lng = fct_f * lng_raw;
 					if (lat > 90.0) {
 						lat = lat - 180.0;}
 					if (lng > 180.0) {
 						lng = lng - 360.0;
	}
 					alt = alt_raw * 100;
 //					fprintf(to, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(to, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);
 //					fprintf(fileairmet, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(filegairmet, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);

 }
// 					var point GeoPoint
// 					point.Lat = lat
// 					point.Lon = lng
// 					point.Alt = alt
// 					points = append(points, point)
// 					f.Points = points

 		    	break;

 		    case 9: // Extended Range 3D Point (AGL). p.47.
 		    	if (record_length < 6) {
 		    		fprintf(to, "Too short\n");
 	 	 			fprintf(filegairmet,  "Too short\n");
 				}
 				else {
 					lng_raw = ((apdu->data[datoff +0]) << 11) | ((apdu->data[datoff +1]) << 3) | ((apdu->data[datoff +2]) & 0xE0 >> 5);
 					lat_raw = (((apdu->data[datoff +2]) & 0x1F) << 14) | ((apdu->data[datoff + 3]) << 6) | (((apdu->data[datoff + 4]) & 0xFC) >> 2);
 					alt_raw = (((apdu->data[datoff + 4]) & 0x03) << 8) | (apdu->data[datoff + 5]);

// 					fprintf(to, "lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);
// 					fprintf(filegairmet, "lat_raw=%d, lng_raw=%d, alt_raw=%d\n", lat_raw, lng_raw, alt_raw);

 					lat = fct_f * lat_raw;
 					lng = fct_f * lng_raw;
 					if (lat > 90.0) {
 						lat = lat - 180.0; }
 					if (lng > 180.0) {
 						lng = lng - 360.0;

 					alt = alt_raw * 100;
 //					fprintf(to, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(to, " Coord: %f,%f  Alt: %d\n", lat, lng,alt);
// 					fprintf(filegairmet, "lat=%f,lng=%f,alt=%f\n", lat, lng, alt);
 					fprintf(filegairmet, " Coord: %f,%f  Alt: %d\n", lat, lng, alt);
 					}
 				}
 				break;
 			}
 			fprintf(to, " Object Type: %s  Object Element: %s\n",ob_type_text,ob_ele_text);
 			fprintf(filegairmet, " Object Type: %s  Object Element: %s\n",ob_type_text,ob_ele_text);
       	}

    	display_generic_data(apdu->data, apdu->length, to);

    	fflush(filegairmet);
    }
    break;

    case 70:
    {
    	int rec_offset=0;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	display_generic_data(apdu->data, apdu->length, to);

    	fprintf(to," woof-71:       %s\n",report);
    }
    break;

    case 71:
    {
    	int rec_offset=0;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	display_generic_data(apdu->data, apdu->length, to);

    	fprintf(to," woof-71:       %s\n",report);
    }
    break;

    case 90:
    {
    	int rec_offset=0;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	display_generic_data(apdu->data, apdu->length, to);

    	fprintf(to," woof-71:       %s\n",report);
    }
    break;

    case 91:
    {
    	int rec_offset=0;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	display_generic_data(apdu->data, apdu->length, to);
    	fprintf(to," woof-71:       %s\n",report);
    }
    break;

    case 413:
    {
    	// Generic text, DLAC
    	int rec_offset=0;
    	const char *text = decode_dlac(apdu->data, apdu->length,rec_offset);
    	const char *report = text;

    	while (report) {
    		char report_buf[1024];
    		const char *next_report;
    		char mtype[9];
    		char *p, *r;
    		char observation[900];
    		char gstn[5];
    		char *pirep_copy;

    		Decoded_METAR MetarStruct,*Mptr = &MetarStruct;

    		next_report = strchr(report, '\x1e'); // RS
    		if (!next_report)
    			next_report = strchr(report, '\x03'); // ETX
    		if (next_report) {
    			memcpy(report_buf, report, next_report - report);
    			report_buf[next_report - report] = 0;
    			report = next_report + 1;
    		} else {
    			strcpy(report_buf, report);
    			report = NULL;
    			}

    		if (!report_buf[0])
    			continue;

    		r = report_buf;
    		p = strchr(r, ' ');    // *** RType ***
    		if (p) {
    			*p = 0;
    			strcpy(observation,r);
    			strncpy(mtype,r,8);
    			fprintf(to," RType: %s\n", r);
    			r = p+1;
    		}
    		p = strchr(r, ' ');   // *** RLoc ***
    		if (p) {
    			*p = 0;
    			strcat(observation," ");
    			strcat(observation,r);
    			if (strcmp(mtype,"PIREP") == 0) {
    				fprintf(to," RLoc:  See Below\n"); }
    			else{
    				if( strcmp(mtype,"WINDS") == 0){
    					strcpy(gstn,"K");
    					strcat(gstn,r);
    				}
    				else if (strcmp(mtype,"METAR") == 0 || strcmp(mtype,"SPECI") == 0   ) {
    					strncpy(gstn,r,5); }
    				else if (strcmp(mtype,"TAF") == 0 || strcmp(mtype,"SPECI") == 0   ) {
    					strncpy(gstn,r,5); }
    				else if (strcmp(mtype,"TAF.AMD") == 0) {
    					strncpy(gstn,r,5); }

    				get_gs_name(gstn,reccount);

    				fprintf(to," RLoc:  %s - %s\n",gstn, gs_ret);
    			}
//    			if( strcmp(mtype,"METAR") == 0 ||
//    					strcmp(mtype,"SPECI") == 0   ){
    			time_t current_time = time(NULL);
    			struct tm *tm = localtime(&current_time);
    			fprintf(filemetar,"Time                 : %s", asctime(tm));
    			fprintf(filemetar,"WX Station           : %s - %s\n",gstn,gs_ret);
 //   			}
    			r = p+1;
    		}
    		p = strchr(r, ' ');   //  *** RTime ***
    		if (p) {
    			*p = 0;
    			strcat(observation," ");
    			strcat(observation,r);
    			if( strcmp(mtype,"METAR") != 0 &&
    					strcmp(mtype,"SPECI") != 0   )
    				fprintf(to," RTime: %s\n", r);
    			r = p+1;
    		}
    		if (strcmp(mtype,"TAF") == 0 || strcmp(mtype,"TAF.AMD") == 0 ||
    				strcmp(mtype,"WINDS") == 0){

    			fprintf(filemetar," Report Name         : %s\n",mtype);
    			fprintf(filemetar," Data:\n%s\n", r);    // *** Text ***
    		}
    		fprintf(to," Text:\n%s\n", r);    // *** Text ***

//   *** METAR ***
    		strcat(observation," ");
    		strcat(observation,r);

    		if (strcmp(mtype,"PIREP") == 0)
    		{
    			pirep_copy = (char *)malloc(strlen(r) + 1);
    			strcpy(pirep_copy,r);

    			get_pirep(pirep_copy,to);
    		}
    		if (strcmp(mtype,"METAR") == 0 || strcmp(mtype,"SPECI") == 0  ) {

    			if( decode_metar(observation, Mptr) != 0 ) {
    				fprintf(to,"Error METAR Decode\n"); }
    			else {
    				print_decoded_metar( Mptr); }
    		}
    		memset(&MetarStruct, 0, sizeof(MetarStruct));
    		fflush(filemetar);
    	}
    }
    break;
    default:
    	display_generic_data(apdu->data, apdu->length, to);
    	break;
    }                
}            

static const char *info_frame_type_names[16] = {

		"FIS-B APDU",
		"Reserved for Developmental Use",
		"Reserved for Future Use (2)",
		"Reserved for Future Use (3)",
		"Reserved for Future Use (4)",
		"Reserved for Future Use (5)",
		"Reserved for Future Use (6)",
		"Reserved for Future Use (7)",
		"Reserved for Future Use (8)",
		"Reserved for Future Use (9)",
		"Reserved for Future Use (10)",
		"Reserved for Future Use (11)",
		"Reserved for Future Use (12)",
		"Reserved for Future Use (13)",
		"Current Report List (14)    ",
		"TIS-B/ADS-R Service Status"
};

static void uat_display_uplink_info_frame(const struct uat_uplink_info_frame *frame, FILE *to)
{
    fprintf(to, "\nINFORMATION FRAME:\n"
    		" Type:  %u (%s)\n",
			frame->type,
			info_frame_type_names[frame->type]);

    if (frame->length > 0) {
    	if (frame->is_fisb)
    		uat_display_fisb_frame(&frame->fisb, to);
        else {
        	int rec_offset=frame->length;
        	if (frame->type == 15) {
        		fprintf(to," ICAO List: \n");
        		int i = 1; int j =0	;
        		while (i < rec_offset ) {
        			if (j % 10 == 0)
        				fprintf(to,"\n");
        			j++;
        			fprintf(to,"%02x%02x%02x ",frame->data[i],frame->data[i+1],frame->data[i+2]);
        			i = i +4;
        		}
        		fprintf(to,"\n");
        	}
        	else if (frame->type == 14){      // report list
        		int tfr;  int lidflag;
        		int prod_range; int num_crl; int rep_yr;
        		int txt; int grph; int i;
        		uint16_t prodt;  uint16_t repid=0;

        		prodt=frame->data[0] <<3 | frame->data[1] >>5;
        		tfr=(frame->data[1] >> 4) & 1;
        		lidflag=(frame->data[1] >> 8) & 1;
        		prod_range = frame->data[2] * 5;
        		num_crl = frame->data[3];

            	fprintf(to,"\n Current Report List\n");
            	fprintf(to," Product: %d -  %s\n",prodt,get_fisb_product_name(prodt));
            	fprintf(to," TFR: %d LID Flag: %d",tfr,lidflag);
    	      	fprintf(to," Number of reports: %d  Range(nm): %d\n",num_crl,prod_range);

        		int j = 4;
        		 for (i = 0; i < num_crl; ++i) {
        			 rep_yr = (frame->data[j] & (~( 1<< 0))) ;
        			 txt = (frame->data[j+1] >> 7) & 1;
        			 grph = (frame->data[j+1] >> 6) & 1;
        			 repid = (frame->data[j+1] & ((1<<6)-1)) << 8 |  frame->data[j+2];
        			 fprintf(to," Report(%d) Year: %d Text: %d Graphic: %d  Report ID: %d \n",
							 i+1,rep_yr,txt,grph,repid);
        			 j=j+3;
        		 }
        		 fprintf(to,"\n");
        	     display_generic_data(frame->data, frame->length, to);
       	}
        	else
        		display_generic_data(frame->data, frame->length, to);
        }
    }
}
void uat_display_uplink_mdb(const struct uat_uplink_mdb *mdb, FILE *to)
{
    fprintf(to,"UPLINK: ");

    fprintf(to," Site: %u  " , mdb->tisb_site_id);
    fprintf(to," Lat: %+.4f%s"
            " Lon: %+.4f%s ",
            mdb->lat, mdb->position_valid ? "" : " ",
            mdb->lon, mdb->position_valid ? "" : " ");

 	time_t current_time = time(NULL);
 	char * tm=ctime(&current_time);
    tm[strlen(tm)-6] = '\0';
    fprintf(to," Time: %s",tm);

    if (mdb->app_data_valid) {
        unsigned i;
        for (i = 0; i < mdb->num_info_frames; ++i)
            uat_display_uplink_info_frame(&mdb->info_frames[i], to);
    }
}
