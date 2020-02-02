package main

import (
	"C"
	"fmt"
	"github.com/syndtr/goleveldb/leveldb"
	"os"
	"sync"
)

var (
	db    *leveldb.DB
	mutex *sync.Mutex
)

//CreateDBService initializes db and mutex
//export createDBService
func createDBService(dbFileName string) int32 {
	if db != nil {
		fmt.Fprintln(os.Stdout, "DBService has already been created")
	}

	dbConnection, err := leveldb.OpenFile(dbFileName, nil)
	if err != nil {
		return 1
	}

	db = dbConnection
	mutex = &sync.Mutex{}
	return 0
}

// closeDBService closes db connection
//export closeDBService
func closeDBService() int32 {
	mutex.Lock()
	defer mutex.Unlock()
	fmt.Fprintln(os.Stdout, "Closing database")
	err := db.Close()
	if err != nil {
		return 1
	}
	return 0
}

// putFileFragmentInDB writes file fragment to db
//export putFileFragmentInDB
func putFileFragmentInDB(fragmentID string, fileFragment string) int32 {
	fmt.Fprintln(os.Stdout, "putting fileFragment in db")
	mutex.Lock()
	defer mutex.Unlock()
	err := db.Put([]byte(fragmentID), []byte(fileFragment), nil)
	if err != nil {
		return 1
	}
	return 0
}

// getFileFragmentFromDB gets file fragment from db
//export getFileFragmentFromDB
func getFileFragmentFromDB(fragmentID string) (string, int32) {
	mutex.Lock()
	defer mutex.Unlock()
	data, err := db.Get([]byte(fragmentID), nil)
	if err != nil {
		return "", 1
	}
	return string(data), 0
}

// removeFileFragmentsFromDB removes file fragments from db
//export removeFileFragmentsFromDB
func removeFileFragmentsFromDB(fileFragmentIDs []string) int32 {

	batch := new(leveldb.Batch)
	for _, fileFragmentID := range fileFragmentIDs {
		batch.Delete([]byte(fileFragmentID))
	}
	mutex.Lock()
	defer mutex.Unlock()
	if err := db.Write(batch, nil); err != nil {
		return 1
	}
	return 0
}

func main() {}
