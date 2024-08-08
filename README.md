# Address-book
the project of implementation address book

本通訊錄收錄user name(小於100字元) 以及電話（手機）號碼（long long int）範圍內
基本上以Ｃ語言實作，為本人之個人專案

內建基本功能：會創造一個名為“contact_people_information”之文檔，可用一般文字編輯器開啟並修改

一版：創造基本功能：包含新增聯絡人、刪除聯絡人、查找聯絡人、顯示所有聯絡人

新增聯絡人：輸入聯絡人資訊（user name 以及號碼）1，若新增成功會印出Success，否則印出Fialed 

顯示所有聯絡人：依序顯示初“contact_people_information”所有聯絡人的資料；有資料的話會印出Success，否則代表檔案內並沒有任何資料．印出 Failed : the file is empty

查找聯絡人：輸入聯絡人的name，顯示所有符合該name的聯絡人並列出

刪除聯絡人：輸入聯絡人的name，會顯示所有符合該name的聯絡人；需選取其中一個聯絡人，接著便會刪除該聯絡人（其他同名的聯絡人放置檔案尾部）
