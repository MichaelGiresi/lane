package utils

import (
	"database/sql"

	_ "github.com/lib/pq"
)

var Db *sql.DB

func InitDB(dataSourceName string) {
	var err error
	Db, err = sql.Open("postgres", dataSourceName)
	if err != nil {
		panic(err)
	}

	if err = Db.Ping(); err != nil {
		panic(err)
	}
}
