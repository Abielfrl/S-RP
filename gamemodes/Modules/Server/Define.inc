//MySQL Configuration
#define     MYSQL_HOST      "127.0.0.1"
#define     MYSQL_USERNAME  "root"
#define     MYSQL_PASSWORD  ""
#define     MYSQL_DATABASE  "scnr"

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 60
#endif 

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif