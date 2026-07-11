# Homepage configuration.
server {
    listen       443 ssl;
    server_name  staging.bourbonwarfare.com staging.bwarma.com;
    http2 off;
    
    proxy_connect_timeout       300;
    proxy_send_timeout          300;
    proxy_read_timeout          300;
    send_timeout                300;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name  staging.bourbonwarfare.com staging.bwarma.com staging.bourbonwarfare.club;

    port_in_redirect off;
    sendfile off;
    proxy_connect_timeout       300;
    proxy_send_timeout          300;
    proxy_read_timeout          300;
    send_timeout                300;

    # Browser endpoints
    location / {
        proxy_pass  http://127.0.0.1:8500;
        
        error_page 403 =302 /login;
    
    }
    
    # Static Endpoints
    location /static/ {
        alias B:/potato_staging/potato_backend/static/;
        open_file_cache off;
        add_header Cache-Control "must-revalidate, proxy-revalidate, max-age=14400";
    }
}