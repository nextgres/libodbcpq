# PostgreSQL to Oracle Migration

**Table of Contents**

* [Tools Needed](#tools-needed)

## Tools Needed

* [MySQL Driver for ODBC](https://github.com/nextgres/oss-libodbcmysql)
* [SQLines Migration](https://github.com/dmtolpeko/sqlines)

## Preparing the Environment

```sh
$ sqlines -s=mysql -t=postgresql -in=script.sql
```

## Migrating Data

```sh
$ sqlines -s=mysql -t=postgresql -in=script.sql
```

## Application Library


