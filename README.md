# Pattern-File-Search
3rd Project in C Systems Information Class. Pattern File Search

We will also test your programs with other input files. Note that you can assume that each line in the files will
contain all the fields. No need to check for malformed files or lines.
Fields:
1. State code (e.g., CA, TX, etc)
2. Timestamp (time of observation as a UNIX timestamp)
3. Geolocation (geohash string)
4. Humidity (0 - 100
5. Snow (1 = snow present, 0 = no snow)
6. Cloud cover (0 - 100
7. Lightning strikes (1 = lightning strike, 0 = no lightning)
8. Pressure (Pa)
9. Surface temperature (Kelvin) 

The times the measurements were taken are expressed as Unix timestamps. These can be converted to string form
with the ctime function. You will also need to divide the timestamps in the data files by 1000 to adjust for the
precision ctime 

