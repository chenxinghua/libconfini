/*	-*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*-	*/

/**

	@file		confini.h
	@brief		libconfini header
	@author		Stefano Gioffr&eacute;
	@copyright 	GNU Public License v3
	@date		2016-2018
	@see		Source code at https://github.com/madmurphy/libconfini/blob/master/src/confini.h

**/

#ifndef _LIBCONFINI_HEADER_
#define _LIBCONFINI_HEADER_

#include <stdint.h>



/* PRIVATE (HEADER-SCOPED) MACROS */


#define _LIBCONFINI_INIFORMAT_DECLARATION_(SIZE, PROPERTY, DEFAULT) unsigned char PROPERTY:SIZE;
#define _LIBCONFINI_INIFORMAT_ASSIGNEMENT_(SIZE, PROPERTY, DEFAULT) DEFAULT,
#define _LIBCONFINI_INIFORMAT_STRUCT_ struct IniFormat { _LIBCONFINI_INIFORMAT_AS_(_LIBCONFINI_INIFORMAT_DECLARATION_) }
#define _LIBCONFINI_DEFAULT_FORMAT_ { _LIBCONFINI_INIFORMAT_AS_(_LIBCONFINI_INIFORMAT_ASSIGNEMENT_) }



/* PUBLIC MACROS */


#define _LIBCONFINI_INIFORMAT_AS_(______)                                   /*-*\

    ______(    BITS    NAME                       DEFAULT VALUE             )/--/
                                                                            /-*/\
    ______(    7,      delimiter_symbol,          INI_EQUALS                )   \
    ______(    1,      case_sensitive,            0                         )/*-/
                                                                            /-*/\
    ______(    2,      semicolon_marker,          INI_DISABLED_OR_COMMENT   )   \
    ______(    2,      hash_marker,               INI_DISABLED_OR_COMMENT   )   \
    ______(    2,      section_paths,             INI_ABSOLUTE_AND_RELATIVE )   \
    ______(    2,      multiline_nodes,           INI_MULTILINE_EVERYWHERE  )/*-/
                                                                            /-*/\
    ______(    1,      no_single_quotes,          0                         )   \
    ______(    1,      no_double_quotes,          0                         )   \
    ______(    1,      no_spaces_in_names,        0                         )   \
    ______(    1,      implicit_is_not_empty,     0                         )   \
    ______(    1,      do_not_collapse_values,    0                         )   \
    ______(    1,      preserve_empty_quotes,     0                         )   \
    ______(    1,      no_disabled_after_space,   0                         )   \
    ______(    1,      disabled_can_be_implicit,  0                         )/*-/
                                                                            /-*/


/** @brief	Checks whether a format does not support escape sequences **/
#define INIFORMAT_HAS_NO_ESC(FMT) (FMT.multiline_nodes == INI_NO_MULTILINE && FMT.no_double_quotes && FMT.no_single_quotes)



/* PUBLIC TYPEDEFS */


/** @brief	24-bit bitfield representing the format of an INI file (INI dialect) **/
typedef _LIBCONFINI_INIFORMAT_STRUCT_ IniFormat;

/** @brief	Global statistics about an INI file **/
typedef struct IniStatistics {
	const IniFormat format;
	const size_t bytes;
	const size_t members;
} IniStatistics;

/** @brief	Dispatch of a single INI node **/
typedef struct IniDispatch {
	const IniFormat format;
	uint8_t type;
	char * data;
	char * value;
	const char * append_to;
	size_t d_len;
	size_t v_len;
	size_t at_len;
	size_t dispatch_id;
} IniDispatch;

/** @brief	The unique ID number of an INI format (24-bit maximum) **/
typedef uint32_t IniFormatNum;



/* PUBLIC FUNCTIONS */


extern int load_ini_file (
	FILE * const ini_file,
	const IniFormat format,
	int (* const f_init) (
		IniStatistics * statistics,
		void * init_other
	),
	int (* const f_foreach) (
		IniDispatch * dispatch,
		void * foreach_other
	),
	void * const user_data
);

extern int load_ini_path (
	const char * const path,
	const IniFormat format,
	int (* const f_init) (
		IniStatistics * statistics,
		void * init_other
	),
	int (* const f_foreach) (
		IniDispatch * dispatch,
		void * foreach_other
	),
	void * const user_data
);

extern _Bool ini_string_match_ss (
	const char * const simple_string_a,
	const char * const simple_string_b,
	const IniFormat format
);

extern _Bool ini_string_match_si (
	const char * const simple_string,
	const char * const ini_string,
	const IniFormat format
);

extern _Bool ini_string_match_ii (
	const char * const ini_string_a,
	const char * const ini_string_b,
	const IniFormat format
);

extern _Bool ini_array_match (
	const char * const ini_string_a,
	const char * const ini_string_b,
	const char delimiter,
	const IniFormat format
);

extern size_t ini_unquote (
	char * const ini_string,
	const IniFormat format
);

extern size_t ini_string_parse (
	char * const ini_string,
	const IniFormat format
);

extern size_t ini_array_get_length (
	const char * const ini_string,
	const char delimiter,
	const IniFormat format
);

extern int ini_array_foreach (
	const char * const ini_string,
	const char delimiter,
	const IniFormat format,
	int (* const f_foreach) (
		const char * fullstring,
		size_t memb_offset,
		size_t memb_length,
		size_t memb_num,
		IniFormat format,
		void * foreach_other
	),
	void * const user_data
);

extern size_t ini_array_shift (
	const char ** const ini_strptr,
	const char delimiter,
	const IniFormat format
);

extern size_t ini_array_collapse (
	char * const ini_string,
	const char delimiter,
	const IniFormat format
);

extern char * ini_array_break (
	char * const ini_string,
	const char delimiter,
	const IniFormat format
);

extern char * ini_array_release (
	char ** ini_strptr,
	const char delimiter,
	const IniFormat format
);

extern int ini_array_split (
	char * const ini_string,
	const char delimiter,
	const IniFormat format,
	int (* const f_foreach) (
		char * member,
		size_t memb_length,
		size_t memb_num,
		IniFormat format,
		void * foreach_other
	),
	void * const user_data
);

extern void ini_global_set_lowercase_mode (
	_Bool lowercase
);

extern void ini_global_set_implicit_value (
	char * const implicit_value,
	const size_t implicit_v_len
);

extern IniFormatNum ini_fton (
	const IniFormat format
);

extern IniFormat ini_ntof (
	IniFormatNum format_id
);

extern signed int ini_get_bool (
	const char * const ini_string,
	const signed int return_value
);



/* PUBLIC LINKS */


extern int (* const ini_get_int) (
	const char * ini_string
);

extern long int (* const ini_get_lint) (
	const char * ini_string
);

extern long long int (* const ini_get_llint) (
	const char * ini_string
);

extern double (* const ini_get_float) (
	const char * ini_string
);



/* PUBLIC CONSTANTS AND VARIABLES */


/** @brief	Error mask (flags not present in user-generated interruptions) -- its value should be considered opaque **/
#define CONFINI_ERROR 252

/** @brief	Error codes -- the actual values of each constant should be considered opaque **/
enum ConfiniInterruptNo {
	CONFINI_IINTR = 1,	/**< Interrupted by the user during `f_init()` **/
	CONFINI_FEINTR = 2,	/**< Interrupted by the user during `f_foreach()` **/
	CONFINI_ENOENT = 4,	/**< File inaccessible **/
	CONFINI_ENOMEM = 5,	/**< Error allocating memory **/
	CONFINI_EIO = 6,	/**< Error reading the file **/
	CONFINI_EFEOOR = 7	/**< The dispatches are more than expected (out of range) **/
};

/** @brief	INI nodes types **/
enum IniNodeType {
	INI_UNKNOWN = 0,
	INI_VALUE = 1,		/**< Not used here (values are dispatched together with keys), but available for user's implementations **/
	INI_KEY = 2,
	INI_SECTION = 3,
	INI_COMMENT = 4,
	INI_INLINE_COMMENT = 5,
	INI_DISABLED_KEY = 6,
	INI_DISABLED_SECTION = 7
};

/** @brief	Most used key-value and array delimiters (but a delimiter may also be any other ASCII character) **/
enum IniDelimiters {
	INI_ANY_SPACE = 0,	/**< In multi-line INIs: `/(?:\\(?:\n\r?|\r\n?)|[\t \v\f])+/`, in non-multi-line INIs: `/[\t \v\f])+/` **/
	INI_EQUALS = '=',	/**< `=` **/
	INI_COLON = ':',	/**< `:` **/
	INI_DOT = '.',		/**< `.` **/
	INI_COMMA = ','		/**< `,` **/
};

/** @brief	Possible values of `IniFormat::semicolon_marker` and `IniFormat::hash_marker` (i.e., meaning of `/\s+[#;]/` in respect to a format) **/
enum IniCommentMarker {
	INI_DISABLED_OR_COMMENT = 0,	/**< This marker opens a comment or a disabled entry **/
	INI_ONLY_COMMENT = 1,		/**< This marker opens a comment **/
	INI_IGNORE = 2,			/**< This marker opens a comment that must be ignored **/
	INI_IS_NOT_A_MARKER = 3		/**< This is a normal character **/
};

/** @brief	Possible values of `IniFormat::section_paths` **/
enum IniSectionPaths {
	INI_ABSOLUTE_AND_RELATIVE = 0,	/**< Section paths starting with a dot express nesting to the current parent, to root otherwise **/
	INI_ABSOLUTE_ONLY = 1,		/**< Section paths starting with a dot will be simply cleaned of their leading dot and appended to root **/
	INI_ONE_LEVEL_ONLY = 2,		/**< The format supports sections, but the dot does not express nesting and is not a meta-character **/
	INI_NO_SECTIONS = 3		/**< The format does *not* support sections -- `/\[[^\]]*\]/g`, if any, will be treated as keys! **/
};

/** @brief	Possible values of IniFormat::multiline_nodes **/
enum IniMultiline {
	INI_MULTILINE_EVERYWHERE = 0,		/**< Comments, section paths and keys -- disabled or not -- are allowed to be multi-line. **/
	INI_BUT_COMMENTS = 1,			/**< Only section paths and keys -- disabled or not -- are allowed to be multi-line. **/
	INI_BUT_DISABLED_AND_COMMENTS = 2,	/**< Only *active* section paths and *active* keys are allowed to be multi-line. **/
	INI_NO_MULTILINE = 3			/**< The multi-line escape sequence is disabled. **/
};

/** @brief	A model format **/
static const IniFormat INI_DEFAULT_FORMAT = _LIBCONFINI_DEFAULT_FORMAT_;

/** @brief	If set to `TRUE`, key and section names in case-insensitive INI formats will be dispatched lowercase, verbatim otherwise (default value: `FALSE`) **/
extern _Bool INI_GLOBAL_LOWERCASE_MODE;

/** @brief	Value to be assigned to implicit keys (default value: `NULL`) **/
extern char * INI_GLOBAL_IMPLICIT_VALUE;

/** @brief	Length of the value assigned to implicit keys -- this may be any unsigned number, independently of the real length of `#INI_GLOBAL_IMPLICIT_VALUE` (default value: `0`) **/
extern size_t INI_GLOBAL_IMPLICIT_V_LEN;



/* CLEAN THE PRIVATE ENVIRONMENT */


#undef _LIBCONFINI_INIFORMAT_DECLARATION_
#undef _LIBCONFINI_INIFORMAT_ASSIGNEMENT_
#undef _LIBCONFINI_INIFORMAT_STRUCT_
#undef _LIBCONFINI_DEFAULT_FORMAT_



/* END OF _LIBCONFINI_HEADER_ */


#endif



/* EOF */

