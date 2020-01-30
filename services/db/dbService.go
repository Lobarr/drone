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
//export CreateDBService
func CreateDBService(dbFileName string) int32 {
	fmt.Fprintln(os.Stdout, dbFileName)
	// if db != nil {
	// 	fmt.Fprintln(os.Stdout, "DBService has already been created")
	// }

	// dbConnection, err := leveldb.OpenFile(dbFileName, nil)
	// if err != nil {
	// 	return 1
	// }

	// db = dbConnection
	// mutex = &sync.Mutex{}
	return 0
}

// CloseDBService closes db connection
//export CloseDBService
func CloseDBService() int32 {
	mutex.Lock()
	defer mutex.Unlock()
	err := db.Close()
	if err != nil {
		return 1
	}
	return 0
}

// PutFileFragment writes file fragment to db
//export PutFileFragment
func PutFileFragment(fragmentID string, fileFragment string) int32 {
	mutex.Lock()
	defer mutex.Unlock()
	err := db.Put([]byte(fragmentID), []byte(fileFragment), nil)
	if err != nil {
		return 1
	}
	return 0
}

// GetFileFragent gets file fragment from db
//export GetFileFragent
func GetFileFragent(fragmentID string) (string, int32) {
	mutex.Lock()
	defer mutex.Unlock()
	data, err := db.Get([]byte(fragmentID), nil)
	if err != nil {
		return "", 1
	}
	return string(data), 0
}

// RemoveFileFragments removes file fragments from db
//export RemoveFileFragments
func RemoveFileFragments(fileFragmentIDs []string) int32 {
	
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
