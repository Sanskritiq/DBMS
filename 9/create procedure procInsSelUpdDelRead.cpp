create procedure procInsSelUpdDelRead
(
in action varchar(10),
in prod_id int = null,
in prod_name varchar(50) = null,
in prod_count_id int = null,
in prod_cost int unsigned = null
)
as
begin
    if action = 'mySelect'
    begin
        select * from PRODUCT;
    end if;
    if action = 'myInsert'
    begin
        insert into PRODUCT(prod_id, prod_name, prod_count_id, prod_cost)
        values(prod_id, prod_name, prod_count_id, prod_cost);
    end if;
    if action = 'myUpdate'
    begin
        update PRODUCT
        set
            PRODUCT.prod_name = prod_name,
            PRODUCT.prod_count_id = prod_count_id,
            PRODUCT.prod_cost = prod_cost
        where PRODUCT.prod_id = prod_id;
    end if;
    if action = 'myDelete'
    begin
        delete from PRODUCT
        where pPRODUCT.rod_id = prod_id;
    end if;
    if action = 'myRead'
    begin
        declare n int default 0;
        declare i int default 0;
        select count(*) from PRODUCT into n;
        set i=0;
            while i<n do
            select * from PRODUCT
            where PRODUCT.prod_id = i+1;
            set i = i+1;
        end while;
    end if;
end//



create procedure procInsSelUpdDelRead
(
@action varchar(10),
@prod_id int = null,
@prod_name varchar(50) = null,
@prod_count_id int = null,
@prod_cost int unsigned = null
)
as
begin
    if @action = 'mySelect'
    begin
        select * from PRODUCT;
    end if;
    if @action = 'myInsert'
    begin
        insert into PRODUCT(prod_id, prod_name, prod_count_id, prod_cost)
        values(@prod_id, @prod_name, @prod_count_id, @prod_cost);
    end if;
    if @action = 'myUpdate'
    begin
        update PRODUCT
        set
            prod_name = @prod_name,
            prod_count_id = @prod_count_id,
            prod_cost = @prod_cost
        where prod_id = @prod_id;
    end if;
    if @action = 'myDelete'
    begin
        delete from PRODUCT
        where prod_id = @prod_id;
    end if;
    if @action = 'myRead'
    begin
        declare n int default 0;
        declare i int default 0;
        select count(*) from PRODUCT into n;
        set i=0;
            while i<n do
            select * from PRODUCT
            where prod_id = i+1;
            set i = i+1;
        end while;
    end if;
end//



create procedure procInsSelUpdDelRead
(
in action varchar(10),
in prod_id int,
in prod_name varchar(50),
in prod_count_id int,
in prod_cost int unsigned
)
if @action = 'mySelect' then
begin
    select * from PRODUCT;
end;
end if;
if @action = 'myInsert' then
begin
    insert into PRODUCT(prod_name, prod_count_id, prod_cost)
    values(@prod_name, @prod_count_id, @prod_cost);
end;
end if;
if @action = 'myUpdate' then
begin
    update PRODUCT
    set
        prod_name = @prod_name,
        prod_count_id = @prod_count_id,
        prod_cost = @prod_cost
    where prod_id = @prod_id;
end;
end if;
if @action = 'myDelete' then
begin
    delete from PRODUCT
    where prod_id = @prod_id;
end;
end if;
if @action = 'myRead' then
begin
    declare n int default 0;
    declare i int default 0;
    select count(*) from PRODUCT into n;
    set i=0;
    while i<n do
    begin
        select * from
        (select * from PRODUCT order by prod_id asc) as T
        where rownum=i+1;
        set i = i+1;
    end;
    end while;
end;
end if;













create procedure procInsSelUpdDelRead
(
@prod_id int = null
)
as
begin
    // if @action = 'mySelect'
    // begin
    //     select * from PRODUCT;
    // end if;
    // if @action = 'myInsert'
    // begin
    //     insert into PRODUCT(prod_id, prod_name, prod_count_id, prod_cost)
    //     values(@prod_id, @prod_name, @prod_count_id, @prod_cost);
    // end if;
    // if @action = 'myUpdate'
    // begin
    //     update PRODUCT
    //     set
    //         prod_name = @prod_name,
    //         prod_count_id = @prod_count_id,
    //         prod_cost = @prod_cost
    //     where prod_id = @prod_id;
    // end if;
    // if @action = 'myDelete'
    // begin
    //     delete from PRODUCT
    //     where prod_id = @prod_id;
    // end if;
    // if @action = 'myRead'
    // begin
    declare n int default 0;
    declare i int default 0;
    select count(*) from PRODUCT into n;
    set i=0;
        while i<n do
        begin
            select * from PRODUCT
            where prod_id = i+1;
            set i = i+1;
        end;
    end while;
    // end if;
end//



alter table PRODUCT
add column category enum('economy', 'premium');
alter table PRODUCT
add column gst int;

delimiter //
create procedure procProdCat
(
    in prod_id int
)
begin
    declare average int default 0;
    declare cost int default 0;
    select avg(prod_cost) from PRODUCT into average;
    select prod_cost from PRODUCT where prod_id = @prod_id into cost;
    if cost > average 
        then
        begin
            update PRODUCT
            set category = 'premium'
            where prod_id = @prod_id;
        end;
    else
        begin
            update PRODUCT
            set category = 'economy'
            where prod_id = @prod_id;
        end;
    end if;
end;//
delimiter ;
delimiter //
create procedure procProdGst
(
    in prod_id int,
    in category enum('economy', 'premium')
)
begin
    declare cat enum('economy', 'premium') default null;
    declare cost int default 0;
    select prod_cost from PRODUCT where prod_id = @prod_id into cost;
    if cat = 'economy'
        then
        begin
            update PRODUCT
            set gst = cost * 0.05
            where prod_id = @prod_id;
        end;
    elseif cat = 'premium'
        then
        begin
            update PRODUCT
            set gst = cost * 0.21
            where prod_id = @prod_id;
        end;
    end if;
end;//
delimiter ;



delimiter //
create function funProdSuppGenString
(
    prod_id int,
    prod_supplier varchar(50)
)
returns varchar(12) deterministic
begin
    declare first_three varchar(3);
    declare next_three varchar(3);
    declare next_next_two varchar(2);
    declare last_three varchar(3);
    declare final varchar(11) default null;
    set @count = (select country from COUNTRY where supplier = @prod_supplier);
    set @prod_name = (select prod_name from PRODUCT where prod_id = @prod_id);
    set first_three = convert(@prod_id, char);
    set first_three = lpad(first_three, 3, '0');
    set next_three = substring(@prod_supplier, -3, 3);
    set next_next_two = substring(@count, 1, 2);
    set last_three = substring(@prod_name, 1, 3);
    set final = (select concat(first_three, next_three, next_next_two, last_three));
    return final;
end;//
delimiter ;




UPDATE PRODUCT
SET category = NULL
WHERE category is not null;



delimiter //
create procedure procInsSelUpdDelRead
(
    IN StatementType varchar(6),
    IN prodName varchar(255),
    IN prodCountry integer,
    IN prod varchar(255),
    IN prodPrice integer,
    IN prodMRP integer
)
if @StatementType = 'Insert' then
    begin
        Insert into Product values (@prodName, @prodCountry, @prod, @prodPrice, @prodMRP, @prodId);
    end;
elseif @StatementType = 'Select' then
    begin
        Select * from Product;
    end;
elseif @StatementType = 'Update' then
    begin
        Update Product set prod_name = @prodName, prod_country = @prodCountry, product = @prod, prod_cost = @prodPrice, prod_mrp = @prodMRP where prod_id = @prodId;
    end;
elseif @StatementType = 'Delete' then
    begin
        Delete from Product where prod_id = @prodId;
    end;
elseif @StatementType = 'Read' then
    begin
        set @total := ( select count(*) from Product)-1;
        while @total >= 0 
			do
            begin
                Select * from Product limit 1 offset 1;
                set @total = @total - 1;
            end;
		end while;
    end;
else 
	begin 
		select * from Product;
    end;
end if//
delimiter ;


-- 2. 
-- altering the existing table 
ALTER TABLE `assignment6`.`Product` 
    ADD COLUMN `category` TINYINT NULL AFTER `prod_mrp`;

delimiter $$
create procedure procProdCat(
    IN prodId integer
) 
begin
    set @avarage := (select avg(prod_cost) from Product);
    set @price := (select prod_cost from Product where prod_id = @prodId);
    if @price > @avarage then
        begin
            Update Product set category = 1 where prod_id = @prodId;
        end;
    else
        begin
            Update Product set category = 0 where prod_id = @prodId;
        end;
    end if;
end $$


-- 3.
alter table `assignment6`.`Product` 
    add column `gst` FLOAT NULL AFTER `category`;

create procedure procProdGst(
    IN prodId integer,
    IN prodCategory integer
)
begin 
    if @prodCategory = 1 then
        begin
            set @gst := (select prod_mrp from Product where prod_id = @prodId) * 0.21;
            Update Product set gst = @gst where prod_id = @prodId;
        end;
    else
        begin
            set @gst := (select prod_mrp from Product where prod_id = @prodId) * 0.05;
            Update Product set gst = @gst where prod_id = @prodId;
        end;
    end if;
end $$

-- 4.