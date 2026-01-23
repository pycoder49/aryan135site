# aryan135site

**For Part 3 Step 5 (Compression):**

I used the `mod_deflate` module. It was enabled through apache, and after enabling compression, the HTML, CSS, and JS responses were showed with the gzip encoding. If you inspected the tab, went to network, and reloaded the page (and then looked for "Content-Encoding") field, you would see that the content served was compressed before being set to the client.<br><br>

**For Part 3 Step 6 (Server name change inside headers):**
Guide followed: https://www.tecmint.com/change-apache-server-name-to-anything-in-server-headers/

To change the http server response hader from the default Apache one to a custome "CSE135 Server" one, I had to configure Apache to explicitily override it using the headers module. I enabled Apache's mod_headers module (found online), which allows the modification of response headers. I then added a header override rule inside my site's SSL virtual host config file to always set the Server header to the custome one. That ensured that change applied to the headers. I also changed "ServerTokens" and "ServerSignature" inside the security.conf config file. Then I restarted the apache2 service and it worked!