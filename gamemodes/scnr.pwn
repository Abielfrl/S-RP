#include <a_samp>
#include <a_mysql>

#include <zcmd>
#include <easydialog>

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_va>

#include <YSI_Server/y_colors>

#define     MYSQL_HOST      "127.0.0.1"
#define     MYSQL_USERNAME  "root"
#define     MYSQL_PASSWORD  ""
#define     MYSQL_DATABASE  "scnr"

main()
{
    return 1;
}

new MySQL:g_sql;

#include "Modules\Server\Define"
#include "Modules\Server\Enum"
#include "Modules\Server\Function"