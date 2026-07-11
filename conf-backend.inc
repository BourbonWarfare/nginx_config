# Homepage configuration.
server {
    listen       443 ssl;
    server_name  hub.bourbonwarfare.com hub.bwarma.com;
    http2 off;
    
    proxy_connect_timeout       300;
    proxy_send_timeout          300;
    proxy_read_timeout          300;
    send_timeout                300;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name  hub.bourbonwarfare.com hub.bwarma.com hub.bourbonwarfare.club;

    port_in_redirect off;
    proxy_connect_timeout       300;
    proxy_send_timeout          300;
    proxy_read_timeout          300;
    send_timeout                300;

    # Browser endpoints
    location / {
        proxy_pass  http://127.0.0.1:12239;

        error_page 403 =302 /login;
    }
    
    # Static Endpoints
    location /static/ {
        alias B:/web/potato_backend/static/;
    }
}
