#if !defined(__COLL__H__)
	#error coll.h must be included
#endif
#if !defined(COLL_ORDINALLIST_CLASS)
	#error COLL_ORDINALLIST_CLASS must be defined
#endif
#if !defined(COLL_ORDINALLIST_KEY)
	#error COLL_ORDINALLIST_KEY must be defined
#endif
#if !defined(COLL_ORDINALLIST_ARG_KEY)
	#error COLL_ORDINALLIST_ARG_KEY must be defined
#endif


// ”––Ú±Ì¿‡
class COLLECTION_IMP COLL_ORDINALLIST_CLASS
{
NO_ASSIGN_OPERATOR(COLL_ORDINALLIST_CLASS);
public:
	COLL_ORDINALLIST_CLASS(LONG nBlockSize=10);
	~COLL_ORDINALLIST_CLASS();
};


#undef COLL_ORDINALLIST_CLASS
#undef COLL_ORDINALLIST_KEY
#undef COLL_ORDINALLIST_ARG_KEY

