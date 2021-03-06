/* got this off net.sources */
#include <stdio.h>
#include <string.h>

/*
 * get option letter from argument vector
 */
int	opterr = 1,		/* useless, never set or used */
	optind = 1,		/* index into parent argv vector */
	optopt;			/* character checked for validity */
const char	*optarg;		/* argument associated with option */

#define BADCH	(int)'?'
#define EMSG	""
#define errmsg(s) fputs(*argv,stderr);fputs(s,stderr); \
		fputc(optopt,stderr);fputc('\n',stderr);return(BADCH);

int
getopt(argc,argv,ostr)
    int	argc;
    const char *argv[];
    char *ostr;
{
	static const char *place = EMSG;	/* option letter processing */
	register char	*oli;		/* option letter list index */
	char	*index();

	if(!*place) {			/* update scanning pointer */
		if(optind >= argc || *(place = argv[optind]) != '-' || !*++place) return(EOF);
		if (*place == '-') {	/* found "--" */
			++optind;
			return(EOF);
		}
	}				/* option letter okay? */
	if ((optopt = (int)*place++) == (int)':' || !(oli = strchr(ostr,optopt))) {
		if(!*place) ++optind;
		errmsg(": illegal option -- ");
	}
	if (*++oli != ':') {		/* don't need argument */
		optarg = NULL;
		if (!*place) ++optind;
	}
	else {				/* need an argument */
		if (*place) optarg = place;	/* no white space */
		else if (argc <= ++optind) {	/* no arg */
			place = EMSG;
			errmsg(": option requires an argument -- ");
		}
	 	else optarg = argv[optind];	/* white space */
		place = EMSG;
		++optind;
	}
	return(optopt);			/* dump back option letter */
}
