# Homepage configuration.
server {
    listen       443 ssl;
    server_name  wiki.bourbonwarfare.com wiki.bwarma.com wiki.bourbonwarfare.club;
    http2 on;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name  wiki.bourbonwarfare.com wiki.bwarma.com wiki.bourbonwarfare.club;

    port_in_redirect off;

    root   B:/web/mediawiki/current/;
    index  index.php

    client_max_body_size 100m;
    client_body_timeout 60s;

    location ~ ^/w/(index|load|api|thumb|opensearch_desc|rest|img_auth)\.php$ {
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_pass unix:/run/php/php8.1-fpm.sock; # or whatever port your PHP-FPM listens on
    }

    # Images
    location /w/images {
        # Separate location for images/ so .php execution won't apply
        add_header X-Content-Type-Options "nosniff";
    }
    location /w/images/deleted {
        # Deny access to deleted images folder
        deny all;
    }
    # MediaWiki assets (usually images)
    location ~ ^/w/resources/(assets|lib|src) {
        try_files $uri 404;
        add_header Cache-Control "public";
        expires 7d;
    }
    # Assets, scripts and styles from skins and extensions
    location ~ ^/w/(skins|extensions)/.+\.(css|js|gif|jpg|jpeg|png|svg|wasm)$ {
        try_files $uri 404;
        add_header Cache-Control "public";
        expires 7d;
    }
    # License and credits files
    location ~ ^/w/(COPYING|CREDITS) {
        default_type text/plain;
    }

    ## Uncomment the following code if you wish to use the installer/updater
    ## installer/updater
    #location /w/mw-config/ {
    #    # Do this inside of a location so it can be negated
    #    location ~ \.php$ {
    #        include /etc/nginx/fastcgi_params;
    #        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
    #        fastcgi_pass 127.0.0.1:9000; # or whatever port your PHP-FPM listens on
    #    }
    #}

    # Handling for Mediawiki REST API, see [[mw:API:REST_API]]
    location /w/rest.php/ {
        try_files $uri $uri/ /w/rest.php?$query_string;
    }

    ## Uncomment the following code for handling image authentication
    ## Also add "deny all;" in the location for /w/images above
    #location /w/img_auth.php/ {
    #    try_files $uri $uri/ /w/img_auth.php?$query_string;
    #}

    # Handling for the article path (pretty URLs)
    location /wiki/ {
        rewrite ^/wiki/(?<pagename>.*)$ /w/index.php;
    }

    # Allow robots.txt in case you have one
    location = /robots.txt {
    }
    # Explicit access to the root website, redirect to main page (adapt as needed)
    location = / {
        return 301 /wiki/;
    }

    # Every other entry point will be disallowed.
    # Add specific rules for other entry points/images as needed above this
    location / {
        return 404;
    }
}