# aryan135site

For Part 3 step 5 (Compression):
I used the `mod_deflate` module. It was enabled through apache, and after enabling compression, the HTML, CSS, and JS responses were showed with the gzip encoding. If you inspected the tab, went to network, and reloaded the page (and then looked for "Content-Encoding") field, you would see that the content served was compressed before being set to the client.