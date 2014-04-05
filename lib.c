#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,val=-1,choice,choice_id,num_domains;
    int *active_domains;
    virConnectPtr conn;
    virDomainPtr vdp;
    char dn[20];
    conn = virConnectOpen("xen:///");

    if (conn == NULL) {
        printf("Error Connecting to xen");
        exit(0);
    }
    else
    {

		//For finding Active Devices
       /* num_domains=virConnectNumOfDomains(conn);
        active_domains=malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(conn, active_domains, num_domains);

        printf("Active domain IDs : \n");
        for (i = 0 ; i < num_domains ; i++) {
            printf("  %d\n", active_domains[i]);
        }
        free(active_domains);
*/
        while(1)
        {
            
		      num_domains=virConnectNumOfDomains(conn);
        	active_domains=malloc(sizeof(int) * num_domains);
	        num_domains = virConnectListDomains(conn, active_domains, num_domains);

        	printf("Active domain IDs : \n");
	        for (i = 0 ; i < num_domains ; i++) {
	            printf("  %d\n", active_domains[i]);
        	}
	        free(active_domains);

		
            printf("1.Suspend\n2.Resume\n3.Stop\n4.Start\n5.exit ");
            scanf("%d",&choice);

          /*printf("\n Please Insert the Active Domian ID ");
            scanf("%d",&choice_id);
  
            vdp=virDomainLookupByID(conn,choice_id);
        */
            switch(choice)
            {
                case 4: //Start 
                      system("sudo xm list");
                      printf("Enter domain name to be started from the above list :");
                      
                      scanf("%s",dn);
		                  vdp=virDomainLookupByName(conn,dn);
                      val=virDomainCreate(vdp);
                      if(val==0)
                        printf("Success\n");
                      else
                        printf("Failed\n");
                       break;
                case 1:/* Suspend */
			printf("\n Please Insert the Active Domian ID ");
	                scanf("%d",&choice_id);
  	
        	       vdp=virDomainLookupByID(conn,choice_id);
		       val=virDomainSuspend(vdp);
                       if(val==0)
                           printf("Success\n");
                       else
                           printf("Failed\n");   
                       break;
                case 2:/* Resume */ 
		       printf("\n Please Insert the Active Domian ID ");
	                scanf("%d",&choice_id);
                        vdp=virDomainLookupByID(conn,choice_id);
		        val=virDomainResume(vdp);
                        if(val==0)                     
                            printf("Success\n");
                        else
                            printf("Failed\n");   
                        break;

                case 3: /* stop */
			printf("\n Please Insert the Active Domian ID ");
	                scanf("%d",&choice_id);
  
            		vdp=virDomainLookupByID(conn,choice_id);
			val=virDomainShutdown(vdp);
                        if(val==0)                     
                            printf("Success\n");
                        else
                            printf("Failed\n");   
                        break;
		case 5:exit(0);
                default:exit(1);
            }
        }
        virConnectClose(conn);
    }
}

