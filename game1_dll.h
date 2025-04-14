#ifdef _WIN32
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT
#endif

DLLIMPORT void description(void);
DLLIMPORT void reset(void);
DLLIMPORT void update(void);
DLLIMPORT void controller(int key, int button);
