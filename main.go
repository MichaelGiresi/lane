package main

import (
	"fmt"
	"lane/handlers"
	"net"
	"net/http"
)

func getLocalIP() string {
	addrs, err := net.InterfaceAddrs()
	if err != nil {
		return ""
	}
	for _, address := range addrs {
		if ipnet, ok := address.(*net.IPNet); ok && !ipnet.IP.IsLoopback() {
			if ipnet.IP.To4() != nil {
				return ipnet.IP.String()
			}
		}
	}
	return ""
}

func main() {
	http.HandleFunc("/users/create", handlers.CreateUser)
	// Add other routes as needed

	ip := getLocalIP()
	if ip == "" {
		fmt.Println("Error retrieving local IP address. Server started and listening on :8080")
	} else {
		fmt.Printf("Server started and listening on %s:8080\n", ip)
	}
	http.ListenAndServe(":8080", nil)
}
