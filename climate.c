/**
 * climate.c
 *
 * Performs analysis on climate data provided by the
 * National Oceanic and Atmospheric Administration (NOAA).
 *
 * Input:    Tab-delimited file(s) to analyze.
 * Output:   Summary information about the data.
 *
 * Compile:  run make
 *
 * Example Run:      ./climate data_tn.tdv data_wa.tdv
 *
 *
 * Opening file: data_tn.tdv
 * Opening file: data_wa.tdv
 * States found: TN WA
 * -- State: TN --
 * Number of Records: 17097
 * Average Humidity: 49.4%
 * Average Temperature: 58.3F
 * Max Temperature: 110.4F
 * Max Temperatuer on: Mon Aug  3 11:00:00 2015
 * Min Temperature: -11.1F
 * Min Temperature on: Fri Feb 20 04:00:00 2015
 * Lightning Strikes: 781
 * Records with Snow Cover: 107
 * Average Cloud Cover: 53.0%
 * -- State: WA --
 * Number of Records: 48357
 * Average Humidity: 61.3%
 * Average Temperature: 52.9F
 * Max Temperature: 125.7F
 * Max Temperature on: Sun Jun 28 17:00:00 2015
 * Min Temperature: -18.7F
 * Min Temperature on: Wed Dec 30 04:00:00 2015
 * Lightning Strikes: 1190
 * Records with Snow Cover: 1383
 * Average Cloud Cover: 54.5%
 *
 * TDV format:
 *
 * CA» 1428300000000»  9prcjqk3yc80»   93.0»   0.0»100.0»  0.0»95644.0»277.58716
 * CA» 1430308800000»  9prc9sgwvw80»   4.0»0.0»100.0»  0.0»99226.0»282.63037
 * CA» 1428559200000»  9prrremmdqxb»   61.0»   0.0»0.0»0.0»102112.0»   285.07513
 * CA» 1428192000000»  9prkzkcdypgz»   57.0»   0.0»100.0»  0.0»101765.0» 285.21332
 * CA» 1428170400000»  9prdd41tbzeb»   73.0»   0.0»22.0»   0.0»102074.0» 285.10425
 * CA» 1429768800000»  9pr60tz83r2p»   38.0»   0.0»0.0»0.0»101679.0»   283.9342
 * CA» 1428127200000»  9prj93myxe80»   98.0»   0.0»100.0»  0.0»102343.0» 285.75
 * CA» 1428408000000»  9pr49b49zs7z»   93.0»   0.0»100.0»  0.0»100645.0» 285.82413
 *
 * Each field is separated by a tab character \t and ends with a newline \n.
 *
 * Fields:
 *      state code (e.g., CA, TX, etc),
 *      timestamp (time of observation as a UNIX timestamp),
 *      geolocation (geohash string),
 *      humidity (0 - 100%),
 *      snow (1 = snow present, 0 = no snow),
 *      cloud cover (0 - 100%),
 *      lightning strikes (1 = lightning strike, 0 = no lightning),
 *      pressure (Pa),
 *      surface temperature (Kelvin)
 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STATES 50

/* TODO: Add elements to the climate_info struct as necessary. */

/*
 * Fields:
1. State code (e.g., CA, TX, etc)
2. Timestamp (time of observation as a UNIX timestamp)
3. Geolocation (geohash string)
4. Humidity (0 - 100
5. Snow (1 = snow present, 0 = no snow)
6. Cloud cover (0 - 100
7. Lightning strikes (1 = lightning strike, 0 = no lightning)
8. Pressure (Pa)
9. Surface temperature (Kelvin)


 */
struct climate_info {

    char code[3];
    //long double timestamp;
    unsigned long num_records;
    long double sum_temperature;
    long double humidity;
    double snow;
    long double cloud_cover;
    double lightning_strikes;
    long double pressure;
    long double surface_temperature;
    double max_temperature;
    double min_temperature;
    long int max_temperature_date;
    long int min_temperature_date;



};

void analyze_file(FILE* file, struct climate_info* states[], int num_states);
void print_report(struct climate_info* states[], int num_states);

int main(int argc, char* argv[]) {


    /* TODO: fix this conditional. You should be able to read multiple files. */
    if (argc<2) {
        //check arguments
        //  printf("%s\n", argv[1]);
        // printf("%s\n", argv[2]);
        printf("Usage: %s tdv_file1 tdv_file2 ... tdv_fileN \n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Let's create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info* states[NUM_STATES] = { NULL };


    int i;
    for (i =1; i < argc; ++i) {

        /* TODO: Open the file for reading */

        FILE* fp;
        fp = fopen(argv[i], "r");
        printf("Opening file: %s\n" , argv[i]);

        /* TODO: If the file doesn't exist, print an error message and move on
         * to the next file. */

        if (fp == NULL) {
            //error check
            printf("Error in opening file.\n");
            return EXIT_FAILURE;
        }


        /* TODO: Analyze the file */
        analyze_file(fp, states, NUM_STATES);


    }

    /* Now that we have recorded data for each file, we'll summarize them: */
    print_report(states, NUM_STATES);

    return 0;
}

void analyze_file(FILE* file, struct climate_info** states, int num_states) {
    const int line_sz = 100;
    char line[line_sz];
    while (fgets(line, line_sz, file) != NULL) {

        /* TODO: We need to do a few things here:
         *
         *       * Tokenize the line.
         *       * Determine what state the line is for. This will be the state
         *         code, stored as our first token.
         *       * If our states array doesn't have a climate_info entry for
         *         this state, then we need to allocate memory for it and put it
         *         in the next open place in the array. Otherwise, we reuse the
         *         existing entry.
         *       * Update the climate_info structure as necessary.
         */


        char* token = strtok(line, "\t\n");
        char* tokenARR[11];
        int i = 0;
        while (token != NULL) {
            tokenARR[i++] = token;
            token = strtok(NULL, "\t\n");

        }


        //element 0 is the state code
        //element 1 is the timestamp
        //element 2 is the geolocation
        //element 3 is the humidity
        //element 4 is the snow
        //element 5 is the cloud cover
        //element 6 is the lightning strikes
        //element 7 is the pressure
        //element 8 is the surface temperature

        struct  climate_info* p = malloc(sizeof(struct climate_info));

        //code token
        strcpy(p->code, tokenARR[0]);

        //timestamp max
        p->max_temperature_date = (atof(tokenARR[1])) / 1000;

        //printf("%Lf", p->timestamp);

        //timstamp min
        p->min_temperature_date = (atof(tokenARR[1])) / 1000;
        //p->timestamp = (atof(tokenARR[1]))/1000;

        //humidity token
        p->humidity = atof(tokenARR[3]);

        //snow token
        p->snow = atof(tokenARR[4]);

        //cloud cover token
        p->cloud_cover = atof(tokenARR[5]);

        //lightning strikes token
        p->lightning_strikes = atof(tokenARR[6]);

        //pressure token
        p->pressure = atof(tokenARR[7]);

        //surface temperature token
        //convert kelvin to fahrenheit
        p->surface_temperature = (atof(tokenARR[8]) - 273.15) * 9 / 5 + 32;

        //max temperature token
        p->max_temperature = (atof(tokenARR[8]) - 273.15) * 9 / 5 + 32;

        //min temperature token
        p->min_temperature = (atof(tokenARR[8]) - 273.15) * 9 / 5 + 32;

        p->num_records = 1;

        for (int i = 0; i < num_states; i++) {
            if (states[i] == NULL) {
                states[i] = p;
                break;
            }
            else if (strcmp(states[i]->code, p->code) == 0) {
                states[i]->num_records++;
                states[i]->sum_temperature += p->surface_temperature;
                if (states[i]->max_temperature <= p->surface_temperature) {
                    states[i]->max_temperature = p->surface_temperature;
                    states[i]->max_temperature_date = p->max_temperature_date;
                }
                if (states[i]->min_temperature >= p->surface_temperature) {
                    states[i]->min_temperature = p->surface_temperature;
                    states[i]->min_temperature_date = p->min_temperature_date;


                }

                states[i]->humidity += p->humidity;
                states[i]->snow += p->snow;
                states[i]->cloud_cover += p->cloud_cover;
                states[i]->lightning_strikes += p->lightning_strikes;

                break;
            }
        }




    }
//file close
    fclose(file);

}


void print_report(struct climate_info* states[], int num_states) {
    printf("States found:\n");
    int i;
    for (i = 0; i < num_states; ++i) {
        if (states[i] != NULL) {
            struct climate_info* info = states[i];
            printf("%s ", info->code);
        }
    }
    printf("\n");

    /* TODO: Print out the summary for each state. See format above. */

//print -- State: TN --
//Number of Records: 17097
//Average Humidity: 49.4%
//Average Temperature: 58.3F
//Max Temperature: 110.4F
//Max Temperature on: Mon Aug 3 11:00:00 2015
//Min Temperature: -11.1F
//Min Temperature on: Fri Feb 20 04:00:00 2015
//Lightning Strikes: 781
//Records with Snow Cover: 107
//Average Cloud Cover: 53.0%
//Average Pressure: 1013.1hPa

    for (i = 0; i < num_states; ++i) {
        if (states[i] != NULL) {
            //printing all the info sum
            struct climate_info* info = states[i];
            printf("State: %s --\n", info->code);
            printf("Number of Records: %ld\n", info->num_records);
            printf("Average Humidity: %.1Lf%%\n", info->humidity / info->num_records);
            printf("Average Temperature: %.1LFF\n", info->sum_temperature / info->num_records);
            printf("Max Temperature: %.1fF\n", info->max_temperature);
            printf("Max Temperature on: %s", ctime(&info->max_temperature_date));
            printf("Min Temperature: %.1fF\n", info->min_temperature);
            printf("Min Temperature on: %s", ctime(&info->min_temperature_date));
            printf("Lightning Strikes: %.0f\n", info->lightning_strikes);
            printf("Records with Snow Cover: %.0f\n", info->snow);
            printf("Average Cloud Cover: %.1Lf%%\n", info->cloud_cover / info->num_records);
            // printf("Average Pressure: %.1LfhPa\n", info->pressure / info->num_records); I'm not sure if you wanted the average pressue because in the examples of print it was not there//
        }
    }

}
