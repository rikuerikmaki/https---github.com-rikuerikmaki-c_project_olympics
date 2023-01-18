#ifndef _PROJECT__H_
	#define _PROJECT__H_
	
	#endif //! _PROJECT__H_

	//struct for medals
	typedef struct {
	    char name[30];
	    unsigned int gold;
	    unsigned int silver;
	    unsigned int bronze;
	} country;
	
	
	void addCountry(country *country_list, char *str);
	void addMedal(country *country_list, char *str);
	void printResults(country *country_list);
	country* loadFile(char *filename, country *country_list);
	
