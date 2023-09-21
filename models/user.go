package models

type User struct {
	ID       int    `json:"id"`
	Username string `json:"username"`
	Password string `json:"password"`
	// Add more fields like "Bio", "ProfilePicture", etc.
}
