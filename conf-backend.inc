# Homepage configuration.
server {
    listen       443 ssl;
    server_name  hub.bourbonwarfare.com hub.bwarma.com;
    http2 off;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name  hub.bourbonwarfare.com hub.bwarma.com hub.bourbonwarfare.club;

    port_in_redirect off;

    # Browser endpoints
    location / {
        proxy_pass  http://127.0.0.1:12239;

        error_page 403 =302 /login;
    }

    # API Endpoints
    location /api(.*)$ {
        proxy_pass  http://127.0.0.1:12239/api$1;
    }
}
