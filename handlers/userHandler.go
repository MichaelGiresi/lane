package handlers

import (
	"encoding/json"
	"lane/models"
	"lane/utils"
	"net/http"
)

func CreateUser(w http.ResponseWriter, r *http.Request) {
	var user models.User

	decoder := json.NewDecoder(r.Body)
	if err := decoder.Decode(&user); err != nil {
		http.Error(w, err.Error(), http.StatusBadRequest)
		return
	}

	// Hash and salt the password before saving it (use bcrypt or similar)

	_, err := utils.Db.Exec("INSERT INTO users (username, password) VALUES ($1, $2)", user.Username, user.Password)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.WriteHeader(http.StatusCreated)
}

// Implement other handlers like GetUser, UpdateUser, DeleteUser, etc.
