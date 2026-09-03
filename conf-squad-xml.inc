# Homepage configuration.
server {
    listen       443 ssl;
    server_name  squad.bourbonwarfare.com squad.bwarma.com;
    http2 on;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    server_name  squad.bourbonwarfare.com squad.bwarma.com;

    port_in_redirect off;

    location / {
        proxy_pass          http://127.0.0.1:12239/auth/remarks;
        proxy_set_header    Host hub.bourbonwarfare.com;
        proxy_ssl_server_name on;

        # Forward real client headers passed through Anubis
        proxy_set_header    X-Real-IP $remote_addr;
        proxy_set_header    X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header    X-Forwarded-Proto $scheme;
        proxy_set_header    CF-Connecting-IP $http_cf_connecting_ip;
    }
    location ^~ /static/ {
        proxy_pass          http://127.0.0.1:12239/static;
        proxy_set_header    Host hub.bourbonwarfare.com;
        proxy_ssl_server_name on;

        # Forward real client headers passed through Anubis
        proxy_set_header    X-Real-IP $remote_addr;
        proxy_set_header    X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header    X-Forwarded-Proto $scheme;
        proxy_set_header    CF-Connecting-IP $http_cf_connecting_ip;
    }
}