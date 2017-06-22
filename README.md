[![Travis-CI][travis-badge]][travis-builds]

[travis-badge]: https://travis-ci.org/KvitkaOlexandr/Lab8HTTPServer.svg?branch=master
[travis-builds]: https://travis-ci.org/KvitkaOlexandr/Lab8HTTPServer/builds
# Lab8HTTP-Server
<dl>
<dt>Tasks:</dt>
<dd> / - відправити у відповідь JSON-об'єкт із інформацією про сервер: </dd>
<dd>{</dd>
<dd>"title": "%SERVER_NAME%",</dd>
<dd>"developer": "%YOUR_NAME_SURNAME%",</dd>
<dd>"time": "%SERVER_TIME%"</dd>
<dd>}</dd>
<dd> /favorites - JSON-список із об'єктів, що позначають список ваших улюблених мов програмування. Кожен такий об'єкт має мати декілька полів, серед яких обов'язково має бути числове поле id із унікальним для кожного об'єкта значенням.</dd>
<dd> /favorites?{key}={value} - JSON-підсписок тих об'єктів зі списку /favorites, у яких поле {key} має значення {value}. Ключ {key}, по якому відбувається фільтрація списку, обрати довільно.</dd>
<dd> /favorites/{id} - JSON-об'єкт зі списку /favorites за ідентифікатором з числовим значенням {id}. Якщо об'єкта із таким значенням ...id не було знайдено, повертати у відповідь HTTP статус 404 Not Found.</dd>
<dd> /file - зчитати вміст файлу data.txt, який попередньо розмістити у директорії data/ проекту. Відправити клієнту JSON-об'єкт, що містить у собі інформацію про назву, розмір (у байтах) і текстовий вміст файлу.</dd>
<dd> /file/data - у відповідь клієнту відправити JSON-список всіх літер у файлі (файл data.txt).</dd>
<dt>Modules:</dt>
<dd>Server - works with data and files</dd>
<dd>languages - describes languages</dd>
